#include "../include/elf32.h"


void get_elf32_header(char *buffer, Elf32_Ehdr **pehdr)
{
    int header_len = sizeof(Elf32_Ehdr) ; 
    memset((void *)*pehdr , 0 , header_len) ;
    memcpy((void *)*pehdr , (void *)buffer , header_len) ; 
} 

void get_program32_table(Elf32_Ehdr ehdr , char *buffer ,Elf32_Phdr **pphdr ,int len)
{
    memset(*pphdr , 0 , len) ; 
    memcpy(*pphdr , buffer+ehdr.e_phoff,len);
}


bool dealelf32(char *buffer ,long flen, int fix)
{
    FILE *fw = NULL ; 
    long ret = 0 ; 
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr)) ; 
    Elf32_Phdr *phdr = NULL ;  
    char *sh_buffer = NULL ; 
    get_elf32_header(buffer , &ehdr) ; 
    int ph_len = ehdr->e_phentsize * ehdr->e_phnum ; 
    phdr = (Elf32_Phdr *)malloc(ph_len);
    get_program32_table(*ehdr , buffer , &phdr,ph_len);

    int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
    sh_buffer =(char *)malloc(sh_len);

    if(fix == ERASE)
    {
        int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
        sh_buffer =(char *)malloc(sh_len);
        Eraser(ehdr , phdr , ph_len , sh_buffer , sh_len,buffer);
    }
    else if(fix == FIX)
    {
        int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
        sh_buffer =(char *)malloc(sh_len);
        Fix(ehdr , phdr , ph_len , sh_buffer , sh_len,buffer) ;
    }
    
    fw = fopen("fix.so","wb") ; 
    if(fw == NULL )
    {
        puts("open fix.so error") ; 
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

void Eraser(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    long flen = ehdr->e_shoff  ; 
    int sectionlen = ehdr->e_shentsize ;
    memset((void *)section , 0 , s_len) ; 
    memcpy((void *)section , buffer+flen , s_len) ; 
    int sectionNum = ehdr->e_shentsize ; 

    for(int i = 0 ; i < sectionNum ; i++)
    {
        Elf32_Shdr *shdr = (Elf32_Shdr *)section + i * sectionlen ;
       
       /* shdr->sh_name =
        shdr->type = 
        shdr->flags = 
        shdr->sh_addr = 
        shdr->sh_offset = 
        shdr->sh_size = 
        shdr->sh_link = 
        shdr->sh_info = 
        shdr->sh_entsize =
        */

    } 

    /*
    ehdr->e_type = BAD16 ; 
    ehdr->e_machine = BAD16 ; 
    ehdr->e_version = BAD32 ; 
    ehdr->e_flags = BAD32 ; 
    */ 
    ehdr->e_entry = 0 ;
    ehdr->e_shoff = 0xbbbbbbbb ;
    ehdr->e_shstrndx = 0x23 ; 
    ehdr->e_shnum = 100 ;
    ehdr->e_shentsize = 0x20 ; 
    
}


void Fix(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    

}