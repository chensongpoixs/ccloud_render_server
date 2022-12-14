package com.chen.cloud;

import com.chen.system.CpuInfo;
import com.chen.system.GPUInfo;
import com.chen.system.SystemGpu;
import com.chen.system.Util;
/**
 * date: 2022-10-10
 * author:chensong
 */
import java.util.List;
import java.util.Optional;

public class CloudRenderServer
{
    static
    {
    //    System.loadLibrary("cloud_game");
       System.loadLibrary("CloudRenderServer");
    }
    public static  native void nativeMethod();


    public static native boolean CloudRenderInit(String server_name, int wan_port, String thrift_server_host, int thrift_server_port, int thrift_client_port);
    public static native boolean CloudRenderLoop();

    public static native void CloudRenderDestory();

    public static  native void CloudGpuinfo(List<GPUInfo> gpuInfos);
    public static native void CloudCpuInfo( CpuInfo cpuInfo);


    public static native void CloudRenderStop();



}
