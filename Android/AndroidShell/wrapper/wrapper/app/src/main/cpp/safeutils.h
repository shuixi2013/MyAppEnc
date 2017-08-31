//
// Created by lu on 2017/8/25.
//

#ifndef WRAPPER_SAFEUTILS_H
#define WRAPPER_SAFEUTILS_H
#include <jni.h>
#include <string.h>
#include <android/log.h>

# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG ,"safeniko", __VA_ARGS__)

jstring charToJstring(JNIEnv *env , char *str);
jobject invokeStaticMethod(JNIEnv *env , char *class_name ,
                           char *method,jobjectArray type , jobjectArray param);

jobject getField(JNIEnv *env , char * class_name ,jobject obj ,char *fieldname ,char *type);
jobject getStaticField(JNIEnv *env , char * class_name  ,char * fieldname, char * type);

void    setFiled(JNIEnv *env , char * class_name ,char * filedname ,jobject obj) ;
void    setStaticField(JNIEnv *env , char * class_name , char * fieldname);


jobject newObject(JNIEnv *env , char * class_name);






#endif //WRAPPER_SAFEUTILS_H
