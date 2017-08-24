#include "elf.h"
#include "utils.h"

void get_elf64_header(char *buffer, Elf64_Ehdr **pehdr); 
void get_program64_table(Elf64_Ehdr ehdr , char *buffer ,Elf64_Phdr **pphdr); 

bool dealelf32(char *buffer, long flen,int fix,char *outname) ;

void Eraser(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);

void Fix(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);