//
// Created by qwedd on 2017/7/11.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dec.h"
#include "base64.h"
#include "TdUtil.h"

int hexcharToInt(char c)
{
    if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
    return 0;
}

void hexstringToBytes(char* hexstring,char* bytes,int hexlength)
{
    for (int i=0 ; i <hexlength ; i+=2) {
        bytes[i/2] = (char) ((hexcharToInt(hexstring[i]) << 4)
                             | hexcharToInt(hexstring[i+1]));
    }
}


int decodehex(const char *str, char *src)
{
    int len = strlen(str) ;
    char hexbyte[3] = {0} ;
    for( int d = 0; d < len ; d += 2 )
    {
        hexbyte[0] = str[d] ;
        hexbyte[1] = str[d+1];
        sscanf( hexbyte, "%X", &src[d/2] );
    }
}


char *decB64(char * str)
{
    int vlen = strlen(str) ;
    int destlen = (vlen * 3) / 4 + 1 ;
    char *result =( char *)malloc(destlen);
    memset(result,0 ,destlen);
    base64_decode(str , result) ;
    char dec[]="NPC233" ;
    for(int i= 0 ; result[i] !='\0' ; i++)
    {
        result[i] = result[i] ^ dec[i % 6] ;
    }
    //result[i]='\0';
    return result ;
}

 char *decHex(const char *str , int key)
{
    int len = strlen(str)/2 ;
    char *src = (char *)malloc(len + 1) ;
    hexstringToBytes((char *)str , src,len *2) ;
    char tmpkey = key & 0xff ;
    for(int i =0 ; i < len ; i++){
        src[i] ^= tmpkey ;
    }
    src[len] ='\0' ;
    return src ;
}