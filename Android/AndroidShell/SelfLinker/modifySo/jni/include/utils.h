
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#define bool int 
#define false 0 
#define true 1 
#define FIX  1
#define ERASE 0 

#define BAD32  0xdeadbeef
#define BAD16  0xbeef
#define BAD64  0xdeadbeefdeadbeef

#define TAG "MY_NDK"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
