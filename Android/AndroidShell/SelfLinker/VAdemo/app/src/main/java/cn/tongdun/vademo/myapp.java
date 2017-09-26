package cn.tongdun.vademo;

import android.app.Application;
import android.content.Context;

/**
 * Created by n on 2017/9/18.
 */

public class myapp extends Application
{
    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        try {
            VirtualCore.getCore().startup(base);
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }
}
