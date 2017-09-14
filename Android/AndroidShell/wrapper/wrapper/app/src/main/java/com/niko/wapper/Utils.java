package com.niko.wapper;

import android.content.Context;
import android.content.res.AssetManager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by n on 2017/8/11.
 */

public class Utils {

    private Context context;
    public void copyassets(String filename,String destfile)
    {
        InputStream in=null;
        OutputStream out=null;
        try{
            AssetManager am=context.getAssets();
            in=am.open("classes.dex");
            out=new FileOutputStream(destfile);
            byte[]bytes=new byte[1024];
            int i;
            while((i=in.read(bytes))!=-1)
                out.write(bytes,0,i);
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                if(in!=null)
                    in.close();
                if(out!=null)
                    out.close();
            }catch(Exception e){
                e.printStackTrace();
            }
        }
    }

    public File getCacheDir(){
        File cache=context.getCacheDir();
        if(!cache.exists())
            cache.mkdirs();
        return cache;
    }

}
