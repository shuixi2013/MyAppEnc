#include "../../include/elf64.h"


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
    if(ehdr == NULL) goto badend ; 
    Elf64_Phdr *phdr = NULL ;  
    char *sh_buffer = NULL ; 
    get_elf64_header(buffer , &ehdr) ; 

    int ph_len = ehdr->e_phentsize * ehdr->e_phnum ; 
    phdr = (Elf64_Phdr *)malloc(ph_len);
    if(phdr == NULL) goto badend ;
    get_program64_table(*ehdr , buffer , &phdr,ph_len);

    int sh_len = ehdr->e_shentsize * ehdr->e_shnum ; 
    sh_buffer =(char *)malloc(sh_len);
    if(sh_buffer == NULL) goto badend; 
    get_section64_table(ehdr , sh_buffer , sh_len ,buffer);

    puts("[+] start encrypt so");
    startencrypt64(ehdr , phdr ,buffer);
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
        if (shdr->sh_type == SHT_STRTAB)
        {
            if(shdr->sh_addr == 0x0 && shdr->sh_offset != 0x0)
            {
                puts("[+]find shstrtable ,start modify strtable"); 
               // modifystrtable64(shdr->sh_offset , shdr->sh_size,buffer);
            }
            continue;
        }
        deal64_section(shdr);
    } 

    printf("[+]remove elf header\n");
    // FOR 7.0 
    ehdr->e_flags = BAD32 ;
    ehdr->e_entry = 0xFF00000000000000 ;
    //ehdr->e_shoff = BAD32 ;
    // modify e_shstrndx is ok 
    //ehdr->e_shstrndx = BAD16; 
    //ehdr->e_shnum = 60 ;
    // ehdr->e_shentsize = 30 ; 
    memcpy(buffer, ehdr , sizeof(Elf64_Ehdr)) ; 
    memcpy(buffer+flen , section, s_len) ; 
    
}

void modifystrtable64(uint64_t off,uint64_t size , char *buffer)
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

//加密section
void startencrypt64(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , char *buffer)
{
    const char mysection[] = ".mytext" ;

    Elf64_Off  shoff  = ehdr->e_shoff ; 
    Elf64_Half shnum  = ehdr->e_shnum ; 
    Elf64_Half shstrtabx = ehdr->e_shstrndx ; 
    Elf64_Shdr *sh_strtab = (Elf64_Shdr *)(buffer + ( shoff + shstrtabx * sizeof(Elf64_Shdr) )) ;
    char *straddr = buffer + sh_strtab->sh_offset ;

    int i ; 
    for(i = 0 ; i < shnum ; i++)
    {
        Elf64_Shdr *shdr = (Elf64_Shdr *)(buffer + (shoff + i * sizeof(Elf64_Shdr) )) ;
        Elf64_Word index = shdr->sh_name ; 
        if(!strcmp(mysection , straddr+index))
        {
            puts("find mytext section");
            Elf64_Off    off  = shdr->sh_offset ; 
            Elf64_Xword  size = shdr->sh_size ;
            char *data = (char *)malloc(size);
            memset(data, 0, size);
            memcpy(data ,buffer+off ,size) ;
            encode(data, size);
            memcpy(buffer+off, data, size );
            free(data); 
        }
    } 
    
}


// 加密特定函数
void startencrypt64func();

void Fix64(Elf64_Ehdr *ehdr , Elf64_Phdr *phdr , 
            int p_len , char *section ,int s_len,char *buffer)
{
    

}