#include <stdio.h>
#include <stdlib.h>
#include "elf.h"
#include <unistd.h>
#include <string.h>



long get_file_len(FILE *p); 


int main(int argc, char **argv)
{
    FILE* fr = NULL;
    long flen = 0;
    FILE* fw = NULL;
    int ph_len = 0;
    char* buffer = NULL;
    char* sh_buffer = NULL;
    Elf32_Ehdr *pehdr = NULL;
    Elf32_Phdr* pphdr = NULL;   
    char arr[2048] = {0} ; 

    if( argc <2 )
    {
        puts("arg error");
        return  0; 
    }
    
    fr = fopen(argv[1] , "rb") ; 
    if(fr == NULL)
    {
        puts("file open error") ;
        goto error ;  
    }

    flen = get_file_len(fr) ; 
    printf("file len is %ld" , flen) ; 
    buffer = (char *)malloc(flen) ;
    if( buffer == NULL)
    {
        puts("malloc error") ; 
        goto error ; 
    }

    size_t result = fread(buffer,1 , flen , fr) ; 
    if(result != flen)
    {
        puts("read error") ; 
        goto error ; 
    }

    fw =fopen("fix.so" ,"wb"); 
    if(fw == NULL)
    {
        puts("open fix.so error") ; 
        goto error ; 
    }
    



error:
    if(fw != NULL)
        fclose(fw) ; 
    if(fr != NULL) 
        fclose(fr) ; 
    if(buffer != NULL)
        free(buffer) ; 
    return 0 ; 
}


long get_file_len(FILE *f)
{
    fseek(f , 0 , SEEK_END) ; 
    return ftell(f) ; 
}


