#include <jni.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <android/log.h>
#include "safeniko.h"
#include "safeutils.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG ,"safeniko", __VA_ARGS__)


JNINativeMethod methods[] = {
        {"decode",  "(Landroid/content/Context;)V",                (void *)mydecode},
        {"decode2", "(Landroid/content/Context;)V",               (void *)mydecode2},
};


void __attribute__((constructor)) first(void)
{
    LOGD("first");
}

void __attribute__((constructor)) second(void)
{
    LOGD("second");
}



void mydecode(JNIEnv *env , jobject obj , jclass clazz , jobject context)
{

}

void mydecode2(JNIEnv *env, jobject obj , jclass clazz , jobject context)
{
    jclass native_class = env->GetObjectClass(context) ;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm ,void *reserved){
    jint result = -1 ;
    if(vm->GetEnv((void **)&genv , JNI_VERSION_1_4) != JNI_OK){
        return result ;
    }

    char ptr[] = "com/niko/wapper/ProxyApplication";
    jclass JniClazz = genv->FindClass(ptr);
    if (JNI_OK == genv->RegisterNatives(JniClazz, methods, NELEM(methods))) {
        LOGD(">> RegisterNatives success");
    } else {
        LOGD(">> ERROR << RegisterNatives failed");
        return -1;
    }
    result = JNI_VERSION_1_4 ;

    return result ;
}



JNIEXPORT void JNI_OnUnLoad(JavaVM *vm, void *reserved) {
    LOGD(">> JNI_OnUnLoad");
    genv->UnregisterNatives(JniClazz);
    genv->DeleteLocalRef(JniClazz);
    LOGD(">> UnregisterNatives");
}
