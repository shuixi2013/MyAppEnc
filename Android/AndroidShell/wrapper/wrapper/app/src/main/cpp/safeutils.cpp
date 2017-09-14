//
// Created by lu on 2017/8/25.
//

#include "safeutils.h"




int getsoaddr()
{

}


jstring charToJstring(JNIEnv *env , char *str)
{
    jstring encode = env->NewStringUTF(str);
    return encode ;

}

jobject invokeStaticMethod(JNIEnv *env , char *class_name ,
                           char *method,char *sig, jobjectArray type , jobjectArray param)
{
    return NULL ;
}

jobject getField(JNIEnv *env , jstring class_name ,jobject obj ,char *fieldname ,char *type)
{
    jclass clazz = env->GetObjectClass(obj);
    jfieldID  id = env->GetFieldID(clazz,fieldname , type);
    if(id == NULL)
    {
        LOGD("get field id is NULL") ;
    }

    jobject  field = env->GetObjectField(obj , id);
    if(field == NULL)
    {
        LOGD("get field failed");
    }

    return  field ;

}

jobject getStaticField(JNIEnv *env , char *class_name  ,char *fieldname, char *type)
{
    jclass jclazz = env->FindClass(class_name) ;
    jfieldID id = env->GetStaticFieldID(jclazz , fieldname , type) ;
    if(id == NULL)
    {
        LOGD("get field id is NULL") ;
    }

    jobject  field = env->GetStaticObjectField(jclazz , id) ;
    if(field == NULL)
    {
        LOGD("get field failed");
    }

    return field ;
}

void  setField(JNIEnv *env , char *class_name ,char *fieldname , char *sig , jobject obj)
{
    jclass jclazz = env->FindClass(class_name);
    if(jclazz == NULL)
    {
        LOGD("find class error");
    }

    jfieldID  id = env->GetFieldID(jclazz,fieldname , sig);
    if(id == NULL)
    {
        LOGD("get field id is NULL") ;
    }





}
void   setStaticField(JNIEnv *env , char  *class_name , char *fieldname , char *sig)
{
    jclass clazz = env->FindClass(class_name);
    if(clazz == NULL)
    {
        LOGD("find class error");
        return ;
    }

    jfieldID  id = env->GetStaticFieldID(clazz,fieldname ,sig);
    if(id == NULL)
    {
        LOGD("get field id is NULL") ;
        return ;
    }

}

jobject newObject(JNIEnv *env , char *class_name)
{
    jclass clazz = env->FindClass(class_name);
    if(clazz == NULL)
    {
        LOGD("find class error");
    }

    jmethodID  initid = env->GetMethodID(clazz , "<init>" , "()V");
    jobject  obj = env->NewObject(clazz , initid);
    return obj ;
}
