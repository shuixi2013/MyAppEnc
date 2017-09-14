//
// Created by lu on 2017/8/25.
//

#ifndef WRAPPER_SAFENIKO_H
#define WRAPPER_SAFENIKO_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void __attribute__((constructor)) first(void);
void __attribute__((constructor)) second(void);


void mydecode(JNIEnv *env , jobject obj , jclass clazz , jobject context);
void mydecode2(JNIEnv *env ,jobject obj , jclass clazz , jobject context);


JNIEnv *genv ;
jclass JniClazz;
#endif //WRAPPER_SAFENIKO_H
