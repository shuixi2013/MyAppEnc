#include "../include/main.h"

/*
    main -> 1 在内存中找到文件的起始地址 
            2 解密 ，解压缩
            3 调用linker
*/
void ShellInit(void){
    int a = 0 ;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    //所有jni方法
    /*
    JNINativeMethod methods[] = {
    };
  */
    if (JNI_OK != (*vm)->GetEnv(vm, (void **) &gEnv, JNI_VERSION_1_6)) {
        return -1;
    }
    LOGD(">> Start JNI_OnLoad");
    /*
    helperJniClazz = (*gEnv)->FindClass(gEnv, ptr);
    if (JNI_OK == (*gEnv)->RegisterNatives(gEnv, helperJniClazz, methods, NELEM(methods))) {
        LOGD(">> RegisterNatives success");
    } else {
        LOGD(">> ERROR << RegisterNatives failed");
        return -1;
    }
    */
    return JNI_VERSION_1_6;
}




JNIEXPORT void JNI_OnUnLoad(JavaVM *vm, void *reserved) {
    (*gEnv)->UnregisterNatives(gEnv, helperJniClazz);
}