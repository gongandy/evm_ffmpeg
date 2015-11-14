/*
 * evm_ffmpeg_convert.c
 *	Description:
 *
 *  Created on: Nov 9, 2015
 *      Author: 章云飞<zhangyf@evmtv.com>
 */
#include "evm_ffmpeg_convert.h"
#include <libavformat/avformat.h>

#define STREAMING_BUFFER_SIZE 	1024 * 1024

static void* convertTask(void *param)
{
	evm_ffmpeg_instance_t *hFp = (evm_ffmpeg_instance_t*)param;
	AVFormatContext *ifmt_ctx = EVM_NULL, *ofmt_ctx = EVM_NULL;
	AVIOContext *avio_in = EVM_NULL, *avio_out = EVM_NULL;
	AVStream *in_stream, *out_stream;
	AVOutputFormat *ofmt = EVM_NULL;
	AVBitStreamFilterContext *vbsf;
	AVPacket pkt, fpkt;
	static evm_u32 first_pkt = 1;
	evm_u8 *avio_buffer = EVM_NULL, *out_buffer = EVM_NULL;
	evm_u32 u32Ret, i;

	/*注册了所有的文件格式和编解码器的库*/
	av_register_all();

	while (1)
	{
		evm_ffmpeg_SemWait(hFp->eventSem, EVM_PORTING_WAITFOREVER);

		evm_ffmpeg_MutexLock(hFp->mutex);

		ifmt_ctx = avformat_alloc_context();

		/*判断文件输入还是内存输入*/
		if (hFp->stInputFilePath.bpath == EVM_TRUE)
		{
			u32Ret = avformat_open_input(&ifmt_ctx, hFp->stInputFilePath.pfilePath, NULL, NULL);
			if (u32Ret < 0)
			{
				evm_ffmpeg_ErrorLog("[convertTask] Could not open input file\n");
				goto end_0;
			}

			hFp->stInputFilePath.bpath = EVM_FALSE;
		}
		else
		{
	//		avio_buffer = (unsigned char*)av_malloc(STREAMING_BUFFER_SIZE);
			avio_in = avio_alloc_context(hFp->pInputMemory, STREAMING_BUFFER_SIZE, 0, NULL, hFp->evm_read_packet, NULL, NULL);
			if (EVM_NULL == avio_in)
			{
				evm_ffmpeg_ErrorLog("[convertTask] avio_alloc_context of input error\n");
				goto end_0;
			}

			ifmt_ctx->pb = avio_in;
			ifmt_ctx->flags = AVFMT_FLAG_CUSTOM_IO;
			u32Ret = avformat_open_input(&ifmt_ctx, NULL, NULL, NULL);
			if (u32Ret < 0)
			{
				evm_ffmpeg_ErrorLog("[convertTask] Could not open input ram\n");
				goto end_0;
			}
		}

		u32Ret = avformat_find_stream_info(ifmt_ctx, NULL);
		if (u32Ret < 0)
			evm_ffmpeg_ErrorLog("[convertTask] Failed to retrieve input stream information");

		//Print detailed information about the input format
		if (hFp->stInputFilePath.bpath == EVM_TRUE)
		{
			av_dump_format(ifmt_ctx, 0, hFp->stInputFilePath.pfilePath, 0);
		}
		else
		{
			av_dump_format(ifmt_ctx, 0, EVM_NULL, 0);
		}

		//输出
		u32Ret = avformat_alloc_output_context2(&ofmt_ctx, NULL, "mpegts", NULL);
		if (u32Ret < 0)
			evm_ffmpeg_ErrorLog("[convertTask] Could not creat output context");

		hFp->pOutputMemory = (unsigned char*)av_malloc(STREAMING_BUFFER_SIZE);
		avio_out =avio_alloc_context(hFp->pOutputMemory, STREAMING_BUFFER_SIZE , 1, NULL, NULL, hFp->evm_write_packet, NULL);
		if (EVM_NULL == avio_out)
		{
			evm_ffmpeg_ErrorLog("[convertTask] avio_alloc_context of output error\n");
			goto end_0;
		}

		ofmt_ctx->pb=avio_out;
		ofmt_ctx->flags=AVFMT_FLAG_CUSTOM_IO;


		ofmt = ofmt_ctx->oformat;
		for (i = 0; i < ifmt_ctx->nb_streams; i++)
		{
			in_stream = ifmt_ctx->streams[i];
			out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
			if (!out_stream)
			{
				u32Ret = AVERROR_UNKNOWN;
				evm_ffmpeg_ErrorLog("Failed allocating output stream");
			}

			u32Ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
			if (u32Ret < 0)
				evm_ffmpeg_ErrorLog("Failed to copy context from input to output stream codec context");

			//why?
			out_stream->codec->codec_tag = 0;
			if (ofmt->flags & AVFMT_GLOBALHEADER)
				out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

			//判断in_filename是H264编码，注册.Create and initialize a bitstream filter
			if (AV_CODEC_ID_H264 == in_stream->codec->codec_id)
			{
				printf("==========av_bitstream_filter_init============\n");
				vbsf = av_bitstream_filter_init("h264_mp4toannexb");
				if (NULL == vbsf)
					evm_ffmpeg_ErrorLog("Init bitstream filter failed");
			}
		}

		if (hFp->stInputFilePath.bpath == EVM_TRUE)
		{
			av_dump_format(ofmt_ctx, 0, hFp->stInputFilePath.pfilePath, 1);
		}
		else
		{
			av_dump_format(ofmt_ctx, 0, EVM_NULL, 1);
		}


		//XXX 写入内存方式MPEG2TS是否需要Write file header，avformat_write_header(ofmt_ctx, NULL);
		u32Ret = avformat_write_header(ofmt_ctx, NULL);
		if (u32Ret < 0)
		{
			evm_ffmpeg_ErrorLog("[convertTask] Error occurred whne writing header\n");
			goto end_0;
		}

		while (1)
		{
			u32Ret = av_read_frame(ifmt_ctx, &pkt);
			if (u32Ret < 0)
				break;

			if (pkt.pts == AV_NOPTS_VALUE && first_pkt)
			{
				pkt.pts = pkt.dts;
				first_pkt = 0;
			}

			in_stream = ifmt_ctx->streams[pkt.stream_index];
			out_stream  = ofmt_ctx->streams[pkt.stream_index];

			pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, 	\
													(enum AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
			pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, 	\
													(enum AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
			pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
			pkt.pos = -1;

			//FIXME 如果是H264编码的 && 不是判0，应该判断video
			if ((AVMEDIA_TYPE_VIDEO == ifmt_ctx->streams[pkt.stream_index]->codec->codec_type) && (AV_CODEC_ID_H264 == in_stream->codec->codec_id))
			{
				fpkt = pkt;
				u32Ret = av_bitstream_filter_filter(vbsf, out_stream->codec, NULL, &fpkt.data, &fpkt.size, pkt.data, pkt.size, pkt.flags & AV_PKT_FLAG_KEY);
				if (u32Ret < 0)
				{
					evm_ffmpeg_ErrorLog("Error bitstream filter\n");
					break;
				}

				pkt.data = fpkt.data;
				pkt.size = fpkt.size;
			}

			/* mux encoded frame */
			u32Ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
			if (u32Ret < 0)
			{
				evm_ffmpeg_ErrorLog( "Error muxing packet\n");
				break;
			}

			av_free_packet(&pkt);
		}

		//Write file trailer
		av_write_trailer(ofmt_ctx);
	}



end_0:

	av_freep(avio_in);
	av_freep(avio_out);

	av_bitstream_filter_close(vbsf);

	avformat_close_input(&ifmt_ctx);

	avformat_free_context(ofmt_ctx);
	return EVM_NULL;
}


ret_code_e evm_ffmpeg_CreatConvertTask(evm_ffmpeg_instance_t *hFp)
{
	evm_s32 s32Ret;
	evm_threadID threadID = EVM_INVALID_ID;

	s32Ret = evm_ffmpeg_CreateThread(&threadID, EVM_NULL, convertTask, (void*)hFp);
	if (EVM_SUCCESS != s32Ret)
		evm_ffmpeg_ErrorLog("[evm_ffmpeg_CreatConvertTask] create task failed.\n");

	return s32Ret;
}



