CC=clang
INCLUDE=../include
COMMON=../common

NFix: main.o utils.o elf32.o elf64.o
	$(CC) -o NFix  main.o utils.o elf32.o elf64.o

main.o: 
	$(CC)  -c  main.c  
utils.o:
	$(CC) -c ${COMMON}/utils.c
elf32.o:
	$(CC) -c ${COMMON}/elf32.c 
elf64.o:
	$(CC) $(DEBUG) -c ${COMMON}/elf64.c
clean:
	rm *.o 

