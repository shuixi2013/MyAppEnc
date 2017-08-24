#include "elf.h"
#include "utils.h"

void get_elf32_header(char *buffer, Elf32_Ehdr **pehdr); 
void get_program32_table(Elf32_Ehdr ehdr , char *buffer ,Elf32_Phdr **pphdr,int len); 
void get_section_table(Elf32_Ehdr *ehdr ,char *section , int s_len ,char *buffer) ; 

bool dealelf32(char *buffer, long flen,int fix,char *outname) ;

void Eraser(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);

void Fix(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char * section ,int s_len,char *buffer);

void deal_section(Elf32_Shdr *section); 

void startencrypt();
