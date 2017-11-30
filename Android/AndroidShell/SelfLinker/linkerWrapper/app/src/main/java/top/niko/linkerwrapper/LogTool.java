package top.niko.linkerwrapper;

import android.util.Log;

import java.util.Objects;

/**
 * Created by n on 2017/9/26.
 */

public class LogTool  {
    public static String TAG = "MY_NDK";

    public  static void dev(String format , Object... data){
        String data2 = String.format(format ,data);
        Log.d(TAG, data2);
    }

    public  static void dev(String data){
        Log.d(TAG,data);
    }

}
