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
    jclass native_class = env->GetObjectClass(context);
    // 获取路径
    jmethodID  getpackgeName = env->GetMethodID(native_class , "getPackageName" , "()Ljava/lang/String;");
    jstring packagename = (jstring)env->CallObjectMethod(context,getpackgeName);
    const char *str = env->GetStringUTFChars(packagename , NULL);
    char dest[128] = {0};
    const char *blank= "/data/data", *c ="/.cache/";
    strcpy(dest , blank) ;
    strcpy(dest , str) ;
    strcpy(dest , c) ;
    LOGD("file dest is %s",dest);


    jint a = mkdir(dest , 777);
    LOGD("create file status %d",a );

    const char *pre = "chmod 755 " ;
    char cmd[128]={0};
    strcpy(cmd , pre) ;
    strcpy(cmd ,  dest);
    LOGD("cmd is %s" , cmd) ;
    jstring  jcmd = charToJstring(env, cmd);



    // exec
    jclass Runtime = env->FindClass("java/lang/Runtime");
    jmethodID getruntime = env->GetStaticMethodID(Runtime , "getRuntime", "()Ljava/lang/Runtime");
    jobject class_obj = env->CallStaticObjectMethod(Runtime , getruntime);
    jclass class_java = env->GetObjectClass(class_obj) ;

    jmethodID  exec = env->GetMethodID(class_java , "exec" , "(Ljava/lang/String;)Ljava/lang/Process;");
    // watch out
    jobject exec_obj = env->CallObjectMethod(class_obj , exec ,cmd);
    jclass exec_class = env->GetObjectClass(exec_obj) ;
    jmethodID  waitfor = env->GetMethodID(exec_class , "waitFor","()I");
    jint result = env->CallIntMethod(exec_obj , waitfor );
    LOGD(" exec command status %d" , result);

    char dest2[128]= {0};
    const char *c2="/.cache/classdex.jar" ;
    strcpy(dest2 , blank);
    strcpy(dest2 , str) ;
    strcpy(dest2 , c2) ;
    LOGD("%s" , dest2);
    env->ReleaseStringUTFChars(packagename,str);

    jmethodID  getApplicationInfo = env->GetMethodID(native_class , "getApplicationInfo","()Landroid/content/pm/ApplicationInfo;");
    jobject  appInfo  = env->CallObjectMethod(context,getApplicationInfo);
    jclass  appInfo_class = env->GetObjectClass(appInfo) ;

    jfieldID sourcedirid = env->GetFieldID(appInfo_class,"publicSourceDir", "Ljava/lang/String") ;

    jstring sourcedir = (jstring)env->GetObjectField(appInfo,sourcedirid);
    const char *strs = env->GetStringUTFChars(sourcedir, NULL);
    char dest3[128]={0};
    strcpy(dest3 , strs) ;
    env->ReleaseStringUTFChars(sourcedir , strs);
    jbyteArray  bytes = env->NewByteArray(65536);
    LOGD("now start doing something") ;

    char *class_dex2 = "assets/gg.so" ;
    jstring class_jar = charToJstring(env, class_dex2) ;
    jclass jar_class = env->FindClass("java/utils/JarFile");
    jobject jar_obj = newObject(env,"java/utils/JarFile");

    jmethodID getentry = env->GetMethodID(jar_class , "getEntry" , "(Ljava/lang/String)Ljava/util/zip/ZipEntry;");
    jobject localzipEntry = env->CallObjectMethod(jar_obj ,getentry , class_jar);



}

void mydecode2(JNIEnv *env, jobject obj , jclass clazz , jobject context)
{
    jclass native_class = env->GetObjectClass(context) ;
    jmethodID  getpackageName = env->GetMethodID(native_class, "getPackageName" , "()Ljava/lang/String");
    jstring packagename = (jstring) env->CallObjectMethod(context , getpackageName);
    char *aa = "android.app.ActivityThread" , *bb ="currentActivityThread" ;
    //jstring jaa = charToJstring(env, aa);
    //jstring jbb = charToJstring(env, bb);
    jobjectArray  pareTyple ;
    jobjectArray  pareValues ;

    jobject currentActivityThread = invokeStaticMethod(env,aa ,bb , pareTyple ,pareValues);
    char *cc = "android.app.ActivityThread" , *dd = "mPackages" ;
    jstring jcc = charToJstring(env, cc);
    jstring jdd = charToJstring(env, dd);

    jobject hashmapobj = newObject(env, "java/util/HashMap");
    hashmapobj = getField(env,cc, currentActivityThread, dd,"java/util/HashMap") ;

    jclass weak_ref = env->FindClass("java/lang/ref/WeakReference") ;
    if(weak_ref == NULL)
    {
        LOGD("weak ref error");
    }

    jmethodID weak_get = env->GetMethod




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
