#include "elf.h"
#include "utils.h"

void get_elf64_header(char *buffer, Elf64_Ehdr **pehdr); 
void get_program64_table(Elf64_Ehdr ehdr , char *buffer ,Elf64_Phdr **pphdr,int len); 
void get_section64_table(Elf64_Ehdr *ehdr , char *section , int s_len ,char *buffer);

bool dealelf64(char *buffer, long flen,int fix,char *outname) ;

void Eraser64(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);

void Fix64(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer);

void deal64_section(Elf64_Shdr *section); 

void modifystrtable64(uint64_t off,uint64_t size , char *buffer);
void startencrypt64();


