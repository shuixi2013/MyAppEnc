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

void get_section_table(Elf32_Ehdr *ehdr ,char *section , int s_len ,char *buffer)
{
    long flen = ehdr->e_shoff  ; 
    int sectionNum = ehdr->e_shnum ; 
    int sectionsize = ehdr->e_shentsize ;
    memset((void *)section , 0 , s_len) ; 
    memcpy((void *)section , buffer+flen , s_len) ; 
}


bool dealelf32(char *buffer ,long flen, int fix,char *outname)
{
    FILE *fw = NULL ; 
    long ret = 0 ; 
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr)) ; 
    if(ehdr == NULL) goto badend ; 
    Elf32_Phdr *phdr = NULL ;  
    char *sh_buffer = NULL ; 
    get_elf32_header(buffer , &ehdr) ; 

    int ph_len = ehdr->e_phentsize * ehdr->e_phnum ; 
    phdr = (Elf32_Phdr *)malloc(ph_len);
    if(phdr == NULL) goto badend ;
    get_program32_table(*ehdr , buffer , &phdr,ph_len);

    int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
    sh_buffer =(char *)malloc(sh_len);
    if(sh_buffer == NULL) goto badend; 
    get_section_table(ehdr , sh_buffer , sh_len ,buffer);
    
    puts("start encrypt so");
    startencrypt();
    
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
    free(ehdr); 
    free(phdr);
    free(sh_buffer);
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
    int sectionNum = ehdr->e_shnum ; 
    int sectionsize = ehdr->e_shentsize ;


    for(int i = 0 ; i < sectionNum ; i++)
    {
        Elf32_Shdr *shdr = (Elf32_Shdr *)(section + i * sectionsize) ;
        if (shdr->sh_type == SHT_STRTAB)
        {
            if(shdr->sh_addr == 0x0 && shdr->sh_offset != 0x0)
            {
                puts("[+]find shstrtable ,start modify strtable"); 
                modifystrtable(shdr->sh_offset , shdr->sh_size,buffer);
            }
            continue;
        }
        deal_section(shdr);
    } 
    
    // FOR 7.0 
    ehdr->e_flags = BAD32 ;
    ehdr->e_entry |= 0xFF000000 ;
    //ehdr->e_shoff = BAD32 ;
    // modify e_shstrndx is ok 
    //ehdr->e_shstrndx = BAD16; 
    //ehdr->e_shnum = 60 ;
    // ehdr->e_shentsize = 30 ; 
    memcpy(buffer, ehdr , sizeof(Elf32_Ehdr)) ; 
    memcpy(buffer+flen , section, s_len) ; 
    
}


void modifystrtable(uint32_t off,uint32_t size , char *buffer)
{
    char *strstart = buffer+off  ; 
    char *data = (char *)malloc(size) ; 
    if(data == NULL)
        data = (char *)malloc(size) ;  
    FILE *fp ; 
    fp =fopen("/dev/urandom","r"); 
    if(NULL == fp)
    {
        puts("[-]error open /dev/urandom");
        return ;
    }
    fread(data , size , 1 , fp) ;
    data[size-1]='\0' ; 
    fclose(fp);
    memcpy(strstart , data ,size);
}

void deal_section(Elf32_Shdr *shdr)
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

void startencrypt()
{

}

void Fix(Elf32_Ehdr *ehdr , Elf32_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    

}