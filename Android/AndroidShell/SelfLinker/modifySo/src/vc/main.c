#include <stdio.h>
#include <stdlib.h>
#include "../../include/elf.h"
#include "../../include/utils.h"
#include "../../include/elf32.h"
#include "../../include/elf64.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    FILE *frmain = NULL ;
    FILE *frshell = NULL ; 
    long flenshell =0  ,flenmain = 0;
    int ph_len = 0;
    char* buffer = NULL;
    char* sh_buffer = NULL;
    bool isDealOk = false ; 
    char arr[2048] = {0} ; 

    if( argc < 4 )
    {
        puts("arg error");
        printf("%s  shell.so  main.so  output.so \n", argv[0]);
        return 0 ; 
    }
    
    frshell = fopen(argv[1] , "rb") ; 
    if(frshell == NULL)
    {
        puts("file open error") ;
        goto error ;  
    }

    flenshell = get_file_len(frshell) ; 
    printf("file len is %ld \n" , flenshell) ; 
    buffer = (char *)malloc(flenshell+1) ;
    if( buffer == NULL)
    {
        puts("malloc error") ; 
        goto error ; 
    }

    size_t result = fread(buffer,1, flenshell , frshell) ; 
    if(result != flenshell)
    {
        puts("error"); 
        goto error ;    
    }

    if(buffer[4] == 0x01)
    {
        puts("32");
        isDealOk = dealelf32(buffer, flenshell,ERASE,argv[2]) ; 
    }else if (buffer[4] == 0x02)
    {
        puts("64");
        isDealOk = dealelf64(buffer,flenshell,ERASE,argv[2]) ;
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
    if(frshell != NULL) 
        fclose(frshell) ; 
    if(buffer != NULL)
        free(buffer) ; 
    return 0 ; 
}











