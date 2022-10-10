package com.chen.cloud;

import com.chen.gpu.GPUInfo;
/**
 * date: 2022-10-10
 * author:chensong
 */
import java.util.List;

public class cloud_game_mgr
{
    static
    {

        System.loadLibrary("cloud_game");
    }
    public native void nativeMethod();


    public native void Gpuinfo(List<GPUInfo> gpuInfos);




//    public native void info(String value);



    public static  void callback()
    {
        System.out.println("In Java");
    }


}
