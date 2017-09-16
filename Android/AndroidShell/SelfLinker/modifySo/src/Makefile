CC=clang
INCLUDE=../include
COMMON=../common

ModLinker: main.o utils.o elf32.o elf64.o
	$(CC) -o ModLinker  main.o utils.o elf32.o elf64.o
main.o: 
	$(CC) $(DEBUG) -c  main.c  
utils.o:
	$(CC) $(DEBUG)  -c ${COMMON}/utils.c
elf32.o:
	$(CC) $(DEBUG)  -c ${COMMON}/elf32.c 
elf64.o:
	$(CC) $(DEBUG) -c ${COMMON}/elf64.c

clean:
	rm *.o 