#include "elf.h"
#include "utils.h"

void get_elf64_header(char *buffer, Elf64_Ehdr **pehdr); 
void get_program64_table(Elf32_Ehdr ehdr , char *buffer ,Elf64_Phdr **pphdr); 