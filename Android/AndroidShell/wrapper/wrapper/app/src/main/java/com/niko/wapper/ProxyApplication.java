package com.niko.wapper;

import android.app.Application;
import android.content.Context;

/**
 * Created by n on 2017/7/24.
 */

public class ProxyApplication extends Application {

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

    }


    public native void decode() ;

    public native void decode2() ;
}


