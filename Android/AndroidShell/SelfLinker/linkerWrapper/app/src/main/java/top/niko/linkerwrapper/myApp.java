package top.niko.linkerwrapper;

import android.app.Application;
import android.content.Context;

/**
 * Created by n on 2017/9/26.
 */

public class myApp extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    protected void attachBaseContext(Context base) {
        LogTool.dev("start it");
        Utils.loadmain();
        super.attachBaseContext(base);
    }


}
