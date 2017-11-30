#include "../include/linker.h"


int linker_init(void *baseaddr){

    if(SDKVERSION >= 24 )
        exit(-1)
    int ret = -1 ;
    // 解析自己的header 
    
    // 重定位，加载需要的so

    return ret ;
}



