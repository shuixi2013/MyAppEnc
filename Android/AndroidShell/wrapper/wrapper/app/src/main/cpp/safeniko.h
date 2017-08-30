//
// Created by lu on 2017/8/25.
//

#ifndef WRAPPER_SAFENIKO_H
#define WRAPPER_SAFENIKO_H

void __attribute__((constructor)) first(void);
void __attribute__((constructor)) second(void);


void mydecode(jobject obj , jclass clazz , jobject context);
void mydecode2(jobject obj , jclass clazz , jobject context);


JNIEnv *genv ;
jclass JniClazz;
#endif //WRAPPER_SAFENIKO_H
