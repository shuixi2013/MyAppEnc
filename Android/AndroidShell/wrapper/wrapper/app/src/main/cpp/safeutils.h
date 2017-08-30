//
// Created by lu on 2017/8/25.
//

#ifndef WRAPPER_SAFEUTILS_H
#define WRAPPER_SAFEUTILS_H
#include <jni.h>

# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))


jstring charToJstring(JNIEnv *env , char *str);
jobject invokeStaticMethod(JNIEnv *env , jstring class_name ,
                           jstring method,jobjectArray type , jobjectArray param);

jobject getField(JNIEnv *env , jstring class_name ,jobject obj ,jstring fieldname );
jobject getStaticField(JNIEnv *env , jstring class_name  ,jstring fieldname);

void    setFild(JNIEnv *env , jstring class_name ,jstring filedname ,jobject obj) ;
void    setStaticFiled(JNIEnv *env , jstring class_name , jstring fieldname);


jobject newObject(JNIEnv *env , jstring class_name);






#endif //WRAPPER_SAFEUTILS_H
