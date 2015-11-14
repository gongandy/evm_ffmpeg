/*
 * evm_porting_socket.c
 * Copyright(C) EnRich DTV Group Co.,Ltd.
 *
 * Description: 
 *
 * Authors: …Úª‘<shenhui@evmtv.com>
 */

//#include "evm_porting/evm_porting.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <malloc.h>

#include "evm_porting_socket.h"
#include "evm_typedef.h"

typedef struct evm_socket_t {
    evm_s32 fd;
    evm_porting_socketType_e type;
    struct sockaddr_in dest;
    evm_bool block;
} evm_porting_sock_t;


ret_code_e evm_porting_ServerSocketOpen(evm_handle* phSocket, evm_u16 port, evm_porting_socketType_e type, evm_bool bBlock)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_s32 s32Type, s32Proto;
    evm_porting_sock_t* pSocket;
    evm_s32 fd = 0xffffffff;
    
    printf("if you need to use this, plsese sure this is ok ........ @mm\n");

    if (EVM_NULL == phSocket)
    {
        s32Ret = EVM_ERR_INVALIDPOINTER;
        goto FAIL;
    }

    if (EVM_PORTING_SOCKTYPE_TCP == type)
    {
        s32Type = SOCK_STREAM;
        s32Proto = IPPROTO_TCP;
        if (!port)
            goto FAIL;
    }
    else if (EVM_PORTING_SOCKTYPE_UDP == type)
    {
        s32Type = SOCK_DGRAM;
        s32Proto = IPPROTO_UDP;
        if (!port)
            goto FAIL;
    }
    else
        goto FAIL;

    fd = socket(AF_INET, s32Type, s32Proto);
    if (fd < 0)
        goto FAIL;

    // set block or non-block
    if (EVM_TRUE == bBlock)
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);
    else
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

    // server
    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr.s_addr = htonl(INADDR_ANY);

    if (EVM_PORTING_SOCKTYPE_TCP == type)
    {
        // do after
    }
    else if (EVM_PORTING_SOCKTYPE_UDP == type)
    {
        evm_s32 ret = bind(fd, (struct sockaddr*)&dest, sizeof(dest));
        if (ret < 0)
        {
            goto FAIL;
        }
    }
    else
    {
        goto FAIL;
    }

    // create socket
    pSocket = malloc(sizeof(evm_porting_sock_t));
    if (EVM_NULL == pSocket)
    {
        s32Ret = EVM_ERR_OUTOFMEMORY;
        goto FAIL;
    }
    pSocket->fd = fd;
    pSocket->block = bBlock;
    pSocket->type = type;
    memcpy(&pSocket->dest, &dest, sizeof(dest));

    *phSocket = (evm_handle)pSocket;

    s32Ret = EVM_SUCCESS;
FAIL:
    if(fd>=0)
    {
        close(fd);
    }
   return s32Ret;
}

ret_code_e evm_porting_ServerSocketClose(evm_handle handle)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_porting_sock_t* hSocket = EVM_NULL;

    if((evm_handle)EVM_NULL == handle)
    {
        s32Ret = EVM_ERR_INVALIDPOINTER;
        goto end;
    }

    hSocket = (evm_porting_sock_t*)handle;

    if (hSocket->fd >= 0)
    {
        close(hSocket->fd);
        free(hSocket);
    }

    s32Ret = EVM_SUCCESS;

end:
    return s32Ret;
}

ret_code_e evm_porting_ClientSocketOpen(evm_handle* phSocket, evm_s8 const* host, evm_u16 port, evm_porting_socketType_e type, evm_bool bBlock)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_s32 s32Type, s32Proto;
    evm_porting_sock_t* pSocket;

    if (EVM_NULL == phSocket)
    {
        s32Ret = EVM_ERR_INVALIDPOINTER;
        goto end;
    }

    if (EVM_PORTING_SOCKTYPE_TCP == type)
    {
        s32Type = SOCK_STREAM;
        s32Proto = IPPROTO_TCP;
        if (!host || !port)
            goto end;
    }
    else if (EVM_PORTING_SOCKTYPE_UDP == type)
    {
        s32Type = SOCK_DGRAM;
        s32Proto = IPPROTO_UDP;
    }
    else
        goto end;

    evm_s32 fd = socket(AF_INET, s32Type, s32Proto);
    if (fd < 0)
        goto end;

    // set block or non-block
    if (EVM_TRUE == bBlock)
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);
    else
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

    // client
    struct sockaddr_in dest;


    if (EVM_PORTING_SOCKTYPE_TCP == type)
    {
        dest.sin_family = AF_INET;
        dest.sin_port = htons(port);
        if (!inet_aton(host, &(dest.sin_addr)))
        {
            struct hostent* h = gethostbyname(host);
            if (h)
                memcpy(&dest.sin_addr, h->h_addr_list[0], sizeof(struct in_addr));
            else
            {
                goto FAIL;
            }
        }

        // connect host
        while (1)
        {
            s32Ret = connect(fd, (struct sockaddr *)&dest, sizeof(dest));

            // if non-block
            if ((s32Ret < 0) && (EVM_TRUE != bBlock))
            {
                if (EINTR == errno)
                    continue;

                if ((EINPROGRESS != errno) && (EAGAIN != errno))
                {
                    if (fd >= 0)
                        close(fd);
                    goto end;
                }

                // wait until we are connected or until abort
                int try = 100;
                fd_set wfds;
                struct timeval tv;
                tv.tv_sec = 0;
                tv.tv_usec = 100 * 1000;
                while (1)
                {
                    FD_ZERO(&wfds);
                    FD_SET(fd, &wfds);

                    s32Ret = select(fd + 1, NULL, &wfds, NULL, &tv);
                    if (s32Ret > 0 && FD_ISSET(fd, &wfds))
                        break;
                    else
                        usleep(50 * 1000);

                    // timeout?
                    if (try-- < 0)
                    {
                        if (fd >= 0)
                            close(fd);

                        s32Ret = EVM_FAILURE;
                        goto end;
                    }
                }
            }
            else if (s32Ret >= 0)
            {
                break;
            }
            else
            {
                if (fd >= 0)
                    close(fd);
                goto end;
            }
        }
    }
    else if (EVM_PORTING_SOCKTYPE_UDP == type)
    {
        evm_s32 so_broadcast = 1;
        setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));

        dest.sin_family = AF_INET;
        dest.sin_port = htons(port);
        if (!host)
        {
            dest.sin_addr.s_addr = htonl(INADDR_ANY);

            evm_s32 ret = bind(fd, (struct sockaddr*)&dest, sizeof(dest));
            if (ret < 0)
            {
                goto FAIL;
            }
        }
        else
        {
            if (!inet_aton(host, &(dest.sin_addr)))
            {
                struct hostent* h = gethostbyname(host);
                if (h)
                    memcpy(&dest.sin_addr, h->h_addr_list[0], sizeof(struct in_addr));
                else
                {
                    goto FAIL;
                }
            }

        }
    }
    else
    {
        goto FAIL;
    }

    // create socket
    pSocket = malloc(sizeof(evm_porting_sock_t));
    if (EVM_NULL == pSocket)
    {
        s32Ret = EVM_ERR_OUTOFMEMORY;
        goto FAIL;
    }
    pSocket->fd = fd;
    pSocket->block = bBlock;
    pSocket->type = type;
    memcpy(&pSocket->dest, &dest, sizeof(dest));

    *phSocket = (evm_handle)pSocket;

    s32Ret = EVM_SUCCESS;
    return s32Ret;
FAIL:
    if(fd >=0)
    {
        close(fd);
    }
end:
   printf("socket error s32Ret=0x%x error no = %d\n",s32Ret, errno);
    return s32Ret;
}

ret_code_e evm_porting_ClientSocketClose(evm_handle handle)
{
    evm_s32 s32Ret = EVM_FAILURE;
    evm_porting_sock_t* hSocket = EVM_NULL;

    if((evm_handle)EVM_NULL == handle)
    {
        s32Ret = EVM_ERR_INVALIDPOINTER;
        goto end;
    }

    hSocket = (evm_porting_sock_t*)handle;

    if (hSocket->fd >= 0)
    {
        close(hSocket->fd);
        free(hSocket);
    }

    s32Ret = EVM_SUCCESS;

end:
    return s32Ret;
}

evm_s32 evm_porting_SocketRecv(evm_handle handle, evm_s8* data, evm_s32 size)
{
    evm_s32 s32Ret = -1;
    evm_porting_sock_t* hSocket = EVM_NULL;

    if((evm_handle)EVM_NULL == handle)
    {
        goto end;
    }
    hSocket = (evm_porting_sock_t*)handle;

    // non-block
    if (EVM_FALSE == hSocket->block)
    {
        struct timeval tv;
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(hSocket->fd, &readfds);

        tv.tv_sec = 0;
        tv.tv_usec = 20 * 1000;
        s32Ret = select(hSocket->fd + 1, &readfds, NULL, NULL, &tv);

        if (s32Ret > 0)
        {
            if (EVM_PORTING_SOCKTYPE_TCP == hSocket->type)
                s32Ret = recv(hSocket->fd, data, size, 0);
            else
            {
#if 1
                struct sockaddr_in src;
                unsigned int srcLen = sizeof(src);

                s32Ret = recvfrom(hSocket->fd, data, size, 0, (struct sockaddr*)&src, &srcLen);
                memset(&hSocket->dest, 0, sizeof(hSocket->dest));
                memcpy(&hSocket->dest, &src, sizeof(hSocket->dest));
#else
                s32Ret = read(hSocket->fd, data, size);
#endif

            }

            if (s32Ret < 0)
            {
                if (errno != EINTR && errno != EAGAIN)
                    s32Ret = -1;
            }
        }
        else if (s32Ret < 0)
            s32Ret = -1;
        else
            s32Ret = 0;
    }
    // block
    else
    {
        if (EVM_PORTING_SOCKTYPE_TCP == hSocket->type)
            s32Ret = recv(hSocket->fd, data, size, 0);
        else
        {
            struct sockaddr_in src;
            unsigned int srcLen = sizeof(src);

            s32Ret = recvfrom(hSocket->fd, data, size, 0, (struct sockaddr*)&src, &srcLen);
            memset(&hSocket->dest, 0, sizeof(hSocket->dest));
            memcpy(&hSocket->dest, &src, sizeof(hSocket->dest));
        }
    }


end:
    return s32Ret;
}

evm_s32 evm_porting_SocketSend(evm_handle handle, evm_s8* data, evm_s32 size)
{
    evm_s32 s32Ret = -1;
    evm_porting_sock_t* hSocket = EVM_NULL;

    if((evm_handle)EVM_NULL == handle)
    {
        goto end;
    }
    hSocket = (evm_porting_sock_t*)handle;

    if (EVM_FALSE == hSocket->block)
    {
        struct timeval tv;
        fd_set writefds;

        FD_ZERO(&writefds);
        FD_SET(hSocket->fd, &writefds);

        tv.tv_sec = 0;
        tv.tv_usec = 100 * 1000;
        s32Ret = select(hSocket->fd + 1, NULL, &writefds, NULL, &tv);

        if (s32Ret > 0)
        {
            if (EVM_PORTING_SOCKTYPE_TCP == hSocket->type)
                s32Ret = send(hSocket->fd, data, size, 0);
            else
                s32Ret = sendto(hSocket->fd, data, size, 0, (struct sockaddr*)&hSocket->dest, sizeof(hSocket->dest));

            if (s32Ret < 0)
            {
                perror(" send -1\n");
                if (errno != EINTR && errno != EAGAIN)
                    s32Ret = -1;
            }

            if (s32Ret == 0)
                printf("socket send 0 byte \n");
        }
        else if (s32Ret < 0)
            s32Ret = -1;
        else
            s32Ret = 0;

    }
    else
    {
        if (EVM_PORTING_SOCKTYPE_TCP == hSocket->type)
            s32Ret = send(hSocket->fd, data, size, 0);
        else
            s32Ret = sendto(hSocket->fd, data, size, 0, (struct sockaddr*)&hSocket->dest, sizeof(hSocket->dest));
    }

end:
    return s32Ret;
}
