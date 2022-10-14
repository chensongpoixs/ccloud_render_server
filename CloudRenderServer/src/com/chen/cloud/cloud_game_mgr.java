package com.chen.cloud;

import com.chen.gpu.GPUInfo;
import com.chen.gpu.SystemGpu;
/**
 * date: 2022-10-10
 * author:chensong
 */
import java.util.List;
import java.util.Optional;

public class cloud_game_mgr
{
    static
    {
    //    System.loadLibrary("cloud_game");
       System.loadLibrary("CloudRenderServer");
    }
    public static  native void nativeMethod();


    public static native boolean cloudrenderinit(String server_name, int wan_port, String thrift_server_host, int thrift_server_port, int thrift_client_port);
    public static native boolean cloudrenderloop();

    public static native void cloudrenderdestroy();

    public static  native void Gpuinfo(List<GPUInfo> gpuInfos);




//    public native void info(String value);



    public static  void callback()
    {
        System.out.println("In Java");
    }


    public static void cppgpuinfo()
    {
        System.out.println("cppgpuinfo");
        Optional<List<GPUInfo>> gpu_infos =  SystemGpu.getGpuInfo();
        if (null != gpu_infos)
        {
            System.out.println("get gpuinfo ok !!! " + gpu_infos.get().size());
            Gpuinfo(gpu_infos.get());
        }
        else
        {
            System.out.println("not find gpu info failed !!!");
        }
    }
}
