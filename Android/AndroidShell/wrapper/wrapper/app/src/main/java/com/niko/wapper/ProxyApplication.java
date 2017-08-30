package com.niko.wapper;

import android.app.Application;
import android.content.Context;

/**
 * Created by n on 2017/7/24.
 */

public class ProxyApplication extends Application {
    // THE FIRST VERSION IS LEANR FROM  ERICKY
    // THANKS HIM
    static {
        System.loadLibrary("safeniko");
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }


    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        decode(base) ;
        decode2(base) ;

    }


    public native void decode(Context context) ;

    public native void decode2(Context context) ;
}


