#include "../include/elf64.h"


void get_elf64_header(char *buffer, Elf64_Ehdr **pehdr)
{
    int header_len = sizeof(Elf64_Ehdr) ; 
    memset((void *)*pehdr , 0 , header_len) ; 
    memcpy((void *)*pehdr, (void *)buffer , header_len);
} 

void get_program64_table(Elf64_Ehdr ehdr , char *buffer ,Elf64_Phdr **pphdr,int len)
{
    memset(*pphdr ,0 ,len) ;
    memcpy(*pphdr , buffer+ehdr.e_phoff ,len) ; 
}

void get_section64_table(Elf64_Ehdr *ehdr , char *section , int s_len ,char *buffer)
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
    phdr = (Elf64_Phdr *)malloc(ph_len);
    get_program64_table(*ehdr , buffer , &phdr,ph_len);

    int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
    sh_buffer =(char *)malloc(sh_len);
    get_section64_table(ehdr , sh_buffer , sh_len ,buffer);

    puts("[+] start encrypt so");
    startencrypt64();

    if(fix == ERASE)
    {
        Eraser64(ehdr , phdr , ph_len , sh_buffer , sh_len,buffer);
    }
    else if(fix == FIX)
    {
        Fix64(ehdr , phdr , ph_len , sh_buffer , sh_len,buffer) ;
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

void Eraser64(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{

    long flen = ehdr->e_shoff  ; 
    int sectionNum = ehdr->e_shnum ; 
    int sectionsize = ehdr->e_shentsize ;
    printf("[+]remove section info\n");
    for(int i = 0 ; i < sectionNum ; i++)
    {
        Elf64_Shdr *shdr = (Elf64_Shdr *)(section + i * sectionsize) ;
        deal64_section(shdr);
    } 

    printf("[+]remove elf header\n");
    // FOR 7.0 
    ehdr->e_flags = BAD32 ;
    ehdr->e_entry |= 0xFF000000 ;
    //ehdr->e_shoff = BAD32 ;
    ehdr->e_shstrndx = BAD16; 
    //ehdr->e_shnum = 60 ;
    // ehdr->e_shentsize = 30 ; 
    memcpy(buffer, ehdr , sizeof(Elf64_Ehdr)) ; 
    memcpy(buffer+flen , section, s_len) ; 
    
}


void deal64_section(Elf64_Shdr *shdr)
{
    // linke will check 
    // strtab
    // dynamic

    Elf64_Word  mtype = shdr->sh_type ; 
    if(mtype == SHT_NULL)
    {
        printf("find SHT_NULL\n") ; 
    }else if (mtype == SHT_SYMTAB)
    {
        puts("[+]find SHT_SYMTAB") ; 
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
        shdr->sh_size   =  0x0 ; 
    }else if (mtype == SHT_STRTAB)
    {
        puts("[-]find SHT_STRTAB") ; 
    }else if(mtype == SHT_RELA) 
    {
        puts("[+]find SHT_RELA") ;
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
        shdr->sh_size   =  0x0 ;  
    }else if (mtype == SHT_HASH)
    {
        puts("[+]find SHT_HASH"); 
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
        shdr->sh_size   =  0x0 ; 
    }else if(mtype == SHT_DYNAMIC)
    {
        puts("[-]find DYNAMIC"); 
    }else if(mtype == SHT_PROGBITS)
    {
        puts("[+]find SHT_PROGBITS") ;
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
        shdr->sh_size   =  0x0 ; 
    }else if(mtype == SHT_REL)
    {
        puts("find SHT_REL");
       // NEED TO TEST
       // shdr->sh_addr   =  0x0 ;
       // shdr->sh_offset =  0x0 ;
       // shdr->sh_size   =  0x0 ; 
    
    }else if(mtype == SHT_GNU_LIBLIST)
    {
        puts("[+]find SHT_GNU_LIBLIST") ;
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
        shdr->sh_size   =  0x0 ; 
    }else if(mtype == SHT_NOTE)
    {
        puts("[+]find SHT_NOTE"); 
        shdr->sh_addr   =  0x0 ;
        shdr->sh_offset =  0x0 ;
        shdr->sh_size   =  0x0 ; 
    }
    
}


void startencrypt64()
{

}

void Fix64(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    

}