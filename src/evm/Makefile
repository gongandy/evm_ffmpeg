
libtest.a : evm_porting_os.o evm_porting_socket.o
	ar -cr $@ evm_porting_os.o evm_porting_socket.o

%.o : %.c
	gcc -c $< -I ../../include/evm/
