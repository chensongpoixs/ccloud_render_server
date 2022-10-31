package com.chen.cloud;

import com.chen.system.CpuInfo;
import com.chen.system.GPUInfo;
import com.chen.system.SystemGpu;
import com.chen.system.Util;

import java.util.List;
import java.util.Optional;

public class CloudRenderCall
{
    public static void CppGpuInfo()
    {
        System.out.println("CppGpuInfo");
        Optional<List<GPUInfo>> gpu_infos =  SystemGpu.getGpuInfo();
        if (null != gpu_infos)
        {
//            nativeMethod();
            CloudRenderServer. CloudGpuinfo(gpu_infos.get());
        }


    }

    public static void CppCpuInfo()
    {
        System.out.println("CppCpuInfo");


        Optional<CpuInfo> cpuInfo = Util.getGpuInfo();
        if (null != cpuInfo && cpuInfo.get() != null)
        {
            CloudRenderServer. CloudCpuInfo(cpuInfo.get());
        }
    }

}
