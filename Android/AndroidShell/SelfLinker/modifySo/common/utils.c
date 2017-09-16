#include "../include/utils.h"


long get_file_len(FILE *f)
{
    fseek(f , 0 , SEEK_END) ; 
    long ret = ftell(f) ;
    rewind(f); 
    return ret ;
}

void encode(char *content ,int len)
{
    unsigned int FLAG[5] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4};
    int i;
    for (i = 0; i < len; i++) {
        //int remainder = i % 5;
        content[i] = ~content[i];
        content[i] ^= FLAG[i%5];
    }
}




