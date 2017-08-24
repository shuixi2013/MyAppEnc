#include <stdio.h>
#include <stdlib.h>

#define bool int 
#define false 0 
#define true 1 
#define FIX  1
#define ERASE 0 

#define BAD32  0xdeadbeef
#define BAD16  0xbeef
#define BAD64  0xdeadbeefdeadbeef

long get_file_len(FILE *p); 