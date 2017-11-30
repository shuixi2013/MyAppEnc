package top.niko.linkerwrapper;

import android.content.Context;
import android.content.res.AssetManager;
import android.renderscript.ScriptGroup;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by n on 2017/9/26.
 */

public class Utils {

    static{
        try {
            System.loadLibrary("shell");
        }catch (Exception e){
            LogTool.dev("gggggg");
        }
    }

    public static void  test(){
        LogTool.dev("666666");
    }

    public void copyfile(Context context){
        InputStream in = null ;
        OutputStream out = null ;
        String cachePath;
        String FilePath = context.getFilesDir().getAbsolutePath();
        String destfile = FilePath+File.separator+"vmp.dex";

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

    }


    public native  static  void loadmain() ;

    public native  static  void  biubiubiu() ;
}
