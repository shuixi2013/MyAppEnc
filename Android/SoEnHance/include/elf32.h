#include "elf.h"
#include "utils.h"

void get_elf32_header(char *buffer, Elf32_Ehdr **pehdr); 
void get_program32_table(Elf32_Ehdr ehdr , char *buffer ,Elf32_Phdr **pphdr,int len); 

bool dealelf32(char *buffer, long flen,int fix) ;

void Eraser(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);

void Fix(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);


