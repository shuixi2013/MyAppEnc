package cn.tongdun.adb_detect;

import android.content.Context;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.os.Build;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Iterator;

public class MainActivity extends AppCompatActivity {
    String TAG ="TD_JAVA";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        //String gg = SystemPro.get("sys.usb.state");
        //tv.setText(gg);
        String usb = "" ;
        String adb = "" ;
        try {
            Process p = Runtime.getRuntime().exec("cat /sys/class/android_usb/android0/state");
            BufferedReader in  = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = null ;
            while((line = in.readLine()) != null)
            {
                usb+=line+"\n";
            }
            Log.d(TAG , usb);
            String remoteadb =  SystemPro.get("service.adb.tcp.port");
            String remoteadb2 = SystemPro.get("persist.adb.tcp.port");

            tv.setText("usb:"+ usb +" \nadb  "+stringFromJNI());


        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
