#include <jni.h>
#include <string>
#include "TdUtils.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_top_niko_linkerwrapper_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    LOGD("heiha");
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT jstring JNICALL
Java_top_niko_linkerwrapper_MainActivity_loadAndFixDex(
        JNIEnv *env,
        jobject clazz , jstring cachepath ,jstring dexpath) {

    std::string hello = "Hello from C++";

    const char *ncachepath = env->GetStringUTFChars(cachepath,NULL);
    const char *ndexpath = env->GetStringUTFChars(dexpath,NULL);
    LOGD("%s" , ncachepath);
    LOGD("%s", ndexpath);

    return env->NewStringUTF(hello.c_str());
}