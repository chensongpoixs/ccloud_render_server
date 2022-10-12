/**
 * date: 2022-10-10
 * author:chensong
 */
package com.chen.gpu;

import org.apache.commons.io.IOUtils;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;


import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class SystemGpu
{
    private static final String REG = "<!DOCTYPE.*.dtd\">";


    /**
     * 通过命令xml格式显卡信息
     *
     * @return xml字符串
     * @throws IOException 获取显卡信息错误
     */
    public static String getGpuXmlInfo() throws IOException {
        Process process;
        String result = "";
//        nvidia-smi -i 0 -q -d UTILIZATION
        process = Runtime.getRuntime().exec("nvidia-smi -q -x");
        try (InputStream inputStream = process.getInputStream()) {
            result = IOUtils.toString(inputStream, StandardCharsets.UTF_8);
        }

        if (process.isAlive()) {
            process.destroy();
        }
        return result;

    }

    public static int size(String value)
    {
        int ret = 0;
        for (int i = 0; i < value.length(); ++i)
        {
//            System.out.println(Integer.parseInt(String.valueOf(value.charAt(i))));

            if (value.charAt(i) == ' ')
            {
                return ret;
            }
            else
            {
                ++ret;
            }
        }
        return ret;
    }

    public  static boolean comp(String value1, String value2)
    {
        int length = size(value1);
        if (length != value2.length())
        {
            return false;
        }
        for (int i = 0; i <length; ++i)
        {
            if (value1.charAt(i) != value2.charAt(i))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * 通过命令xml格式显卡信息
     *
     * @return xml字符串
     * @throws IOException 获取显卡信息错误
     **/
    public static String getGpuEncodeDecodeInfo(String cmd  ) throws IOException
    {
        Process process;
        String result = "";
//        nvidia-smi -i 0 -q -d UTILIZATION
        process = Runtime.getRuntime().exec( cmd /*" nvidia-smi -i 0 -q -d UTILIZATION"*/);
        try (InputStream inputStream = process.getInputStream()) {
            result = IOUtils.toString(inputStream, StandardCharsets.UTF_8);
        }

        if (process.isAlive()) {
            process.destroy();
        }
        return result;

    }


    public static  gpuVideo  convertGpuVideo(String gpu_video)
    {
        gpuVideo video_info = new gpuVideo();

        String key = "" ;
        String value = "";
        int indexkey = 0;
        int indexvalue = 0;
        boolean read_key = true;
        for (int i = 0; i <gpu_video.length(); ++i)
        {
            if (gpu_video.charAt(i) == '\r')
            {
                if ((i + 1)  < gpu_video.length() &&  gpu_video.charAt((i + 1)) == '\n')
                {
                    {
                        if (key.equals( "Encoder"))
                        {
                            video_info.setVideoEncode( value);
                        }
                        else if ( key.equals("Decoder"))
                        {
                            video_info.setVideoDecode(String.valueOf(value));
                        }
                    }
                }
            }
            else if (gpu_video.charAt(i) == ' '  || gpu_video.charAt(i) == '%' )
            {

            }
            else if (gpu_video.charAt(i) == '\n')
            {
                read_key = true;
                indexkey  = 0;
                indexvalue = 0;
                key = "";
                value = "";
            }
            else if (gpu_video.charAt(i) == ':')
            {
                read_key = false;

            }
            else
            {
                if (read_key)
                {
                    key +=gpu_video.charAt(i);
                }
                else
                {
                    value +=gpu_video.charAt(i);
                }
            }

        }

        return video_info;
    }

    /**
     * 获取gpu信息（暂时只支持nvidia-smi）
     *
     * @return gpu信息集合
     * @throws DocumentException xml解析错误
     */
    public static List<GPUInfo> convertXmlToGpuObject(String xmlGpu) throws DocumentException {
        //忽略dtd
        xmlGpu = xmlGpu.replaceAll(REG, "");
        Document document = DocumentHelper.parseText(xmlGpu);
        List<Element> gpu = document.getRootElement().elements("gpu");
        List<GPUInfo> gpuInfoList = new ArrayList<>();
        gpu.forEach(element -> {
            GPUInfo gpuInfo = new GPUInfo();
            String uuid = element.element("uuid").getText();
            String gpu_index = element.element("gpu_module_id").getText();
            String gpu_cmd  = "nvidia-smi -i "+gpu_index+"  -q -d UTILIZATION";
            gpuInfo.setGpuIndex(gpu_index);
            Optional<String> gpu_info= getGpuEncode_Decode_Info(gpu_cmd );
            if (gpu_info != null)
            {
                gpuVideo video_info =  convertGpuVideo(gpu_info.get());
                gpuInfo.setVideoEncode(video_info.getVideoEncode());
                gpuInfo.setVideoDecode(video_info.getVideoDecode());

            }

            Element fbMemoryUsage = element.element("fb_memory_usage");
            String total = fbMemoryUsage.element("total").getText();
            String used = fbMemoryUsage.element("used").getText();
            String free = fbMemoryUsage.element("free").getText();
            gpuInfo.setTotalMemory(total);
            gpuInfo.setUsedMemory(used);
            gpuInfo.setFreeMemory(free);
            gpuInfo.setName(uuid);
//            Element processes = element.element("processes");
//            List<Element> infos = processes.elements("process_info");
//            List<ProcessInfo> processInfos = new ArrayList<>();
//            infos.forEach(info -> {
//                ProcessInfo processInfo = new ProcessInfo();
//                String pid = info.element("pid").getText();
//                String name = info.element("process_name").getText();
//                String usedMemory = info.element("used_memory").getText();
//                processInfo.setPid(pid);
//                processInfo.setName(name);
//                processInfo.setUsedMemory(usedMemory);
//                processInfos.add(processInfo);
//            });
//            gpuInfo.setProcessInfos(processInfos);
            int intTotal = Integer.parseInt(total.split(" ")[0]);
            int intUsed = Integer.parseInt(used.split(" ")[0]);
            gpuInfo.setUsageRate((int) ((float) intUsed / intTotal * 100));
            gpuInfoList.add(gpuInfo);
        });
        return gpuInfoList;

    }
    /**
     * 获取gpu信息
     *
     * @return gpu信息集合
     */
    public static Optional<List<GPUInfo>> getGpuInfo()
    {
        try {
            String gpuXmlInfo = getGpuXmlInfo();
//            System.out.println(gpuXmlInfo);
            List<GPUInfo> gpuInfos = convertXmlToGpuObject(gpuXmlInfo);
            return Optional.of(gpuInfos);
        } catch (Exception e) {
//            System.out.println("获取gpu信息error , message : {}", e.getMessage(), e);
            return Optional.empty();
        }
    }

    /**
     * 获取gpu信息
     *
     * @return gpu信息集合
     */
    public static Optional<String> getGpuEncode_Decode_Info(String cmd)
    {
        try {
            String gpuXmlInfo = getGpuEncodeDecodeInfo(cmd);
//            System.out.println(gpuXmlInfo);
//            List<GPUInfo> gpuInfos = convertXmlToGpuObject(gpuXmlInfo);
            return Optional.of(gpuXmlInfo);
        } catch (Exception e) {
//            System.out.println("获取gpu信息error , message : {}", e.getMessage(), e);
            return Optional.empty();
        }
    }
}
