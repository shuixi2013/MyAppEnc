CC=clang
INCLUDE=../include
COMMON=../common

NEdit: main.o utils.o elf32.o
	$(CC) -o NEdit  main.o utils.o elf32.o

main.o: 
	$(CC) $(DEBUG) -c  main.c  
utils.o:
	$(CC) $(DEBUG)  -c ${COMMON}/utils.c
elf32.o:
	$(CC) $(DEBUG)  -c ${COMMON}/elf32.c 
clean:
	rm *.o 

