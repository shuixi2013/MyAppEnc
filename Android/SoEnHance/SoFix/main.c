#include <stdio.h>
#include <stdlib.h>
#include "../include/elf.h"
#include "../include/utils.h"
#include "../include/elf32.h"
#include "../include/elf64.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    FILE* fr = NULL;
    long flen = 0;
    int ph_len = 0;
    char* buffer = NULL;
    char* sh_buffer = NULL;
    bool isDealOk = false ; 
    char arr[2048] = {0} ; 

    if( argc <3 )
    {
        puts("arg error");
        return 0 ; 
    }
    
    fr = fopen(argv[1] , "rb") ; 
    if(fr == NULL)
    {
        puts("file open error") ;
        goto error ;  
    }

    flen = get_file_len(fr) ; 
    printf("file len is %ld \n" , flen) ; 
    buffer = (char *)malloc(flen+1) ;
    if( buffer == NULL)
    {
        puts("malloc error") ; 
        goto error ; 
    }

    size_t result = fread(buffer,1, flen , fr) ; 
    if(result != flen)
    {
        puts("error"); 
        goto error ;    
    }

    if(buffer[4] == 0x01)
    {
        puts("32");
        isDealOk = dealelf32(buffer, flen,FIX,argv[2]) ;
    }else if (buffer[4] == 0x01)
    {
        puts("64");
        isDealOk = dealelf64(buffer,flen,FIX,argv[2]) ;
    }else
    {
        puts(" this is error"); 
        goto error ; 
    }
    if(isDealOk)
    {
        puts("deal with it") ; 
    }else
    {
        puts("gg ,not deal with it");
    }
    
error:
    if(fr != NULL) 
        fclose(fr) ; 
    if(buffer != NULL)
        free(buffer) ; 
    return 0 ; 
}











