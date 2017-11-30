#include "../include/main.h"

/*
    main -> 1 在内存中找到文件的起始地址  mmap
            2 解密 ，解压缩
            3 调用linker
*/
void ShellInit(void){
    LOGD("Shell init start");

}

void Mloadmain(){
    LOGD("start decrypt so");
}


void Mbiubiubiu(){
    LOGD("gg2");
}


JNIEnv *gEnv;
jclass utils_class
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    //所有jni方法
    
    char classname[] = "top/niko/linkerwrapper/Utils";
    JNINativeMethod methods[] = {
        {"loadmain", "()V" , (void *)Mloadmain} ,
        {"biubiubiu", "()V",(void *)Mbiubiubiu}
    };
    
    if (JNI_OK != (*vm)->GetEnv(vm, (void **) &gEnv, JNI_VERSION_1_6)) {
        return -1;
    }
    LOGD(">> Start JNI_OnLoad");
    
    utils_class = (*gEnv)->FindClass(gEnv,classname);
    if (JNI_OK == (*gEnv)->RegisterNatives(gEnv,utils_class, methods, NELEM(methods))) {
        LOGD(">> RegisterNatives success");
    } else {
        LOGD(">> ERROR << RegisterNatives failed");
        return -1;
    }
    
    return JNI_VERSION_1_6;
}




JNIEXPORT void JNI_OnUnLoad(JavaVM *vm, void *reserved) {
   (*gEnv)->UnregisterNatives(gEnv, utils_class);
}