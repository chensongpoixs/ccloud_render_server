package com.chen.system;
//;

import org.apache.commons.io.IOUtils;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Util
{

    public static String Cmmmod(String cmd) throws IOException
    {
        Process process;
        String result = "";
//        nvidia-smi -i 0 -q -d UTILIZATION
        process = Runtime.getRuntime().exec(cmd);
        try (InputStream inputStream = process.getInputStream())
        {
            result = IOUtils.toString(inputStream, StandardCharsets.UTF_8);
        }

        if (process.isAlive())
        {
            process.destroy();
        }
        return result;

    }

    public static CpuInfo  GetCpuInfo(String cpu) throws IOException
    {
        CpuInfo cpuInfo = null;
//        List<CpuInfo> cpu_infos = new ArrayList<>();
//        String cmd_cpu_info = "typeperf \"processor(_total)\\% processor time\" -sc 1";
//        String result = Cmmmod(cmd_cpu_info);
//        System.out.println(result);
        int line = 0;
        boolean one = false;
        String data_time = "";
        String cpu_precent = "";
//        String temp = "";
        for (int i = 0; i < cpu.length(); ++i)
        {
//            System.out.println(cpu.charAt(i));
             if (cpu.charAt(i) == '\n')
             {

                 ++line;
                 if (line == 3)
                 {
                     cpuInfo = new CpuInfo(data_time, cpu_precent);


                    return cpuInfo;
                 }
             }
             else if (cpu.charAt(i) != '"' && cpu.charAt(i) != '\r' && cpu.charAt(i) != ',')
             {
                 if (line == 2)
                 {
                     if (one == false)
                     {
                         data_time += cpu.charAt(i);
                     }
                     else
                     {
                         cpu_precent += cpu.charAt(i);
                     }
                 }
             }
             else if (cpu.charAt(i) == ',' && line == 2)
             {
                 one = true;
             }
        }


        return cpuInfo;
    }

    public  static  Optional< CpuInfo > getGpuInfo()
    {
        try {
            String cmd_cpu_info = "typeperf \"processor(_total)\\% processor time\" -sc 1";
            String result = Cmmmod(cmd_cpu_info);
//            System.out.println(result);
             CpuInfo  cpuInfos = GetCpuInfo(result);
            System.out.println(cpuInfos.toString());
            return Optional.of(cpuInfos);
        } catch (Exception e) {
//            System.out.println("获取gpu信息error , message : {}", e.getMessage(), e);
            return Optional.empty();
        }
    }
}
