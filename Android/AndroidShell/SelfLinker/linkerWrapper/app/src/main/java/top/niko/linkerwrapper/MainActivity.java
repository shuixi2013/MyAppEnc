package top.niko.linkerwrapper;

import android.content.Context;
import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class MainActivity extends AppCompatActivity {
    public String cachePath;
    public String destfile;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public String  copyfile(Context context){
        InputStream in = null ;
        OutputStream out = null ;

        String FilePath = context.getFilesDir().getAbsolutePath();
        String destfile = FilePath+ File.separator+"vmp.dex";

        File cacheDir = context.getCacheDir() ;

        if(cacheDir == null){
            cachePath = context.getFilesDir().getAbsolutePath();
        } else {
            cachePath = cacheDir.getAbsolutePath();
        }
        AssetManager assetMgr = context.getAssets();

        try{
            in = assetMgr.open("classes.dex");
            out = new FileOutputStream(destfile);
            byte[] bytes =new byte[1024] ;
            int i ;
            while((i =in.read(bytes)) != -1)
                out.write(bytes,0,i);
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            try{
                if(in != null)
                    in.close();
                if(out != null)
                    out.close();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        return cachePath;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        copyfile(this);
        loadAndFixDex(cachePath,destfile);

        new Thread(new Runnable() {
            @Override
            public void run() {
                LogTool.dev("start Decode");
                String dexpath = copyfile(MainActivity.this);
                String cache = MainActivity.this.getCacheDir().getAbsolutePath();
                LogTool.dev(dexpath);
                LogTool.dev(cache);
                loadAndFixDex(cache,dexpath);
            }
        }).start();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();


    public native String loadAndFixDex(String cachepath , String dexpath);
}
