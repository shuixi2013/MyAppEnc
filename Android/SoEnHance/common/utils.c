#include "../include/utils.h"


long get_file_len(FILE *f)
{
    fseek(f , 0 , SEEK_END) ; 
    long ret = ftell(f) ;
    rewind(f); 
    return ret ;
}



