#include "../include/elf64.h"


void get_elf64_header(char *buffer, Elf64_Ehdr **pehdr)
{
    int header_len = sizeof(Elf64_Ehdr) ; 
    memset((void *)*pehdr , 0 , header_len) ; 
    memcpy((void *)*pehdr, (void *)buffer , header_len);
} 

void get_program64_table(Elf64_Ehdr ehdr , char *buffer ,Elf64_Phdr **pphdr)
{
    memset(*pphdr ,0 ,len) ;
    memcpy(*pphdr , buffer+ehar.e_phoff ,len) ; 
}

void get_section_table(Elf64_Ehdr *ehdr , char *section , int s_len ,char *buffer)
{
    long flen = ehdr->e_shoff  ; 
    int sectionNum = ehdr->e_shnum ; 
    int sectionsize = ehdr->e_shentsize ;
    memset((void *)section , 0 , s_len) ; 
    memcpy((void *)section , buffer+flen , s_len) ; 
}

bool dealelf64(char *buffer ,long flen, int fix,char *outname)
{
    FILE *fw = NULL ; 
    long ret = 0 ; 
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)malloc(sizeof(Elf64_Ehdr)) ; 
    Elf64_Phdr *phdr = NULL ;  
    char *sh_buffer = NULL ; 
    get_elf64_header(buffer , &ehdr) ; 

    int ph_len = ehdr->e_phentsize * ehdr->e_phnum ; 
    phdr = (Elf32_Phdr *)malloc(ph_len);
    get_program64_table(*ehdr , buffer , &phdr,ph_len);

    int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
    sh_buffer =(char *)malloc(sh_len);
    get_section_table(ehdr , sh_buffer , sh_len ,buffer);

    if(fix == ERASE)
    {
        Eraser(ehdr , phdr , ph_len , sh_buffer , sh_len,buffer);
    }
    else if(fix == FIX)
    {
        Fix(ehdr , phdr , ph_len , sh_buffer , sh_len,buffer) ;
    }
    
    fw = fopen(outname,"wb") ; 
    if(fw == NULL )
    {
        puts("open output file error") ; 
        goto badend ; 
    }

    ret = fwrite(buffer, sizeof(char) * flen , 1 , fw) ;
    fclose(fw);
    return true ;

badend:
    return false;
}


/*
* ehdr 
*phdr  program
*p_len progarm 长度
*section 还未指向section，只是一片内存
*s_len section 长度
*buffer 文件内容
*/

void Eraser(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    long flen = ehdr->e_shoff  ; 
    int sectionNum = ehdr->e_shnum ; 
    int sectionsize = ehdr->e_shentsize ;

    for(int i = 0 ; i < sectionNum ; i++)
    {
        Elf32_Shdr *shdr = (Elf64_Shdr *)(section + i * sectionsize) ;
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
    } 

    ehdr->e_shoff = BAD32 ;
    ehdr->e_shstrndx = 0 ; 
    ehdr->e_shnum =0 ;
    ehdr->e_shentsize = BAD16 ; 
    memcpy(buffer, ehdr , sizeof(Elf64_Ehdr)) ; 
    memcpy(buffer+flen , section, s_len) ; 
    
}




void Fix(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    

}