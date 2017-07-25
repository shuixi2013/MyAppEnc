CC=clang
INCLUDE=../include
COMMON=../common

NFix: main.o utils.o elf32.o
	$(CC) -o NFix  main.o utils.o elf32.o

main.o: 
	$(CC)  -c  main.c  
utils.o:
	$(CC) -c ${COMMON}/utils.c
elf32.o:
	$(CC) -c ${COMMON}/elf32.c 
clean:
	rm *.o 

