package cn.tongdun.adb_detect;

import android.util.Log;

import java.lang.reflect.Method;

/**
 * Created by n on 2017/8/7.
 */

public class SystemPro {

    public static String get(String key){

        String value = "" ;
        Class<?> cls = null ;
        try{
            cls = Class.forName("android.os.SystemProperties") ;
            Method mget = cls.getDeclaredMethod("get", String.class) ;
            Object obj = cls.newInstance() ;
            value = (String)mget.invoke(obj,key);
            return value;
        }catch (Exception e){
            Log.e("TD_JAVA", "gggg");
        }
        return null;
    }


}
