/**
 * date: 2022-10-10
 * author:chensong
 */
package com.chen.system;

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


//    public static String GetMttGpuCountInfo(String cmd)
//    {
//        getcommand();
//    }


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
    public static String getcommand(String cmd  ) throws IOException
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
                        else if (key.equals("Gpu"))
                        {
                            video_info.setGpu(value);
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
            if (video_info.getVideoDecode().length() > 0&&  video_info.getVideoEncode().length() > 0)
            {
               break;
            }
        }

        return video_info;
    }

    /**
     *
     * @param gpuinfo
     * @return
     */
    public static List<GPUInfo> ParseMttGpuCountInfo(String gpuinfo)
    {
        List<GPUInfo>  gpuinfos = new ArrayList<>();


//        String key = "";
//        String value = "";

        String gpuname = "";
        boolean read = false;
        for (int i = 0; i < gpuinfo.length(); ++i)
        {
            if (gpuinfo.charAt(i) == ':')
            {
                gpuname = "";
                read = true;
            }
            else if (gpuinfo.charAt(i) == '(')
            {
                GPUInfo info = new GPUInfo();
                info.setName(gpuname);
                info.setGpuIndex( String.valueOf(gpuinfos.size()));
                gpuinfos.add(info);
            }
            else if (gpuinfo.charAt(i) == '\n')
            {
                gpuname = "";
                read = false;
            }
            else if (gpuinfo.charAt(i) != ' ')
            {
                gpuname +=gpuinfo.charAt(i);
            }
        }


        return gpuinfos;
    }

    public static GPUInfo  PareseMttGpuAllInfo(String gpu_info)
    {
        System.out.println("[all gpu info cmd = "+ gpu_info+"]");
        GPUInfo info_ptr = null;
        String key = "" ;
        String value = "";
        int indexkey = 0;
        int indexvalue = 0;
        boolean read_key = true;
        for (int i = 0; i < gpu_info.length(); ++i)
        {
            if (gpu_info.charAt(i) == '\n')
            {
//                System.out.println("[key = "+key+"]["+ value +"]");
                if (key.equals( "Total"))
                {
                    if (info_ptr == null)
                    {
                        info_ptr = new GPUInfo();
                    }
                    info_ptr.setTotalMemory(value);
                }
                else if ( key.equals("Used"))
                {
                    if (info_ptr == null)
                    {
                        info_ptr = new GPUInfo();
                    }
                    info_ptr.setUsedMemory(value);
                }
                else if (key.equals("Free"))
                {
                    if (info_ptr == null)
                    {
                        info_ptr = new GPUInfo();
                    }
                    info_ptr.setFreeMemory(value);
                }
                else if (key.equals("Gpu"))
                {
                    if (info_ptr == null)
                    {
                        info_ptr = new GPUInfo();
                    }
                    info_ptr.setUsageRate(Integer.parseInt(value) );
                }
                else if (key.equals("Encoder"))
                {
                    if (info_ptr == null)
                    {
                        info_ptr = new GPUInfo();
                    }
                    info_ptr.setVideoEncode( value );
                }
                else if (key.equals("Decoder"))
                {
                    if (info_ptr == null)
                    {
                        info_ptr = new GPUInfo();
                    }
                    info_ptr.setVideoDecode( value );
                }
                read_key = true;
                indexkey  = 0;
                indexvalue = 0;
                key = "";
                value = "";
            }
            else if (gpu_info.charAt(i) == ' '  || gpu_info.charAt(i) == '%' || gpu_info.charAt(i) == '\t')
            {
//                System.out.println("' '[key = "+key+"]["+ value +"]");
            }
            else if (gpu_info.charAt(i) == ':')
            {
                read_key = false;
//                System.out.println(":[key = "+key+"]["+ value +"]");
            }
            else
            {
//                System.out.println("[cur char = "+ gpu_info.charAt(i) +"][key = "+key+"]["+ value +"]");
                if (read_key)
                {
                    key +=gpu_info.charAt(i);
                }
                else
                {
                    value +=gpu_info.charAt(i);
                }
            }
        }



        return info_ptr;
    }

    public static List<GPUInfo> GetAllMttGpuInfos(List<GPUInfo> old_gpu_infos)
    {
        List<GPUInfo> new_gpu_infos = new ArrayList<>();


        String key = "";
        String value = "";



        return new_gpu_infos;
    }



    public static List<GPUInfo> convertGpuObject(String gpuarrayinfo)
    {
        List<GPUInfo> gpuInfoList = new ArrayList<>();





        return gpuInfoList;
    }
    /**
     * 获取gpu信息（暂时只支持nvidia-smi）
     *
     * @return gpu信息集合
     * @throws DocumentException xml解析错误
     */
    public static List<GPUInfo> convertXmlToGpuObject(String xmlGpu) throws DocumentException
    {
        //忽略dtd
        xmlGpu = xmlGpu.replaceAll(REG, "");
        Document document = DocumentHelper.parseText(xmlGpu);
        List<Element> gpu = document.getRootElement().elements("gpu");
        List<GPUInfo> gpuInfoList = new ArrayList<>();
        gpu.forEach(element -> {
            GPUInfo gpuInfo = new GPUInfo();
            String uuid = element.element("product_name").getText();
//            String gpu_index = element.element("gpu_module_id").getText();
            String gpu_cmd  = "nvidia-smi -i "+gpuInfoList.size()+"  -q -d UTILIZATION";
            gpuInfo.setGpuIndex(String.valueOf( gpuInfoList.size()));
            Optional<String> gpu_info= getGpuEncode_Decode_Info(gpu_cmd );
            if (gpu_info != null)
            {
                gpuVideo video_info =  convertGpuVideo(gpu_info.get());
                gpuInfo.setVideoEncode(video_info.getVideoEncode());
                gpuInfo.setVideoDecode(video_info.getVideoDecode());
                gpuInfo.setUsageRate(Integer.parseInt(video_info.getGpu()));
            }

            Element fbMemoryUsage = element.element("fb_memory_usage");
            String total = fbMemoryUsage.element("total").getText();
            String used = fbMemoryUsage.element("used").getText();
            String free = fbMemoryUsage.element("free").getText();
            gpuInfo.setTotalMemory(total);
            gpuInfo.setUsedMemory(used);
            gpuInfo.setFreeMemory(free);
            gpuInfo.setName(uuid);

            System.out.println(gpuInfo.ToString());
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
            // nvidia-smi  --list-gpus
            String cmd = "nvidia-smi  --list-gpus";
            String gpuXmlInfo = getGpuXmlInfo();
//            String gpuarrayinfo = getcommand(cmd);
//            System.out.println(gpuXmlInfo);
            List<GPUInfo> gpuInfos = convertXmlToGpuObject(gpuXmlInfo);
            return Optional.of(gpuInfos);
        } catch (Exception e) {
//            System.out.println("获取gpu信息error , message : {}", e.getMessage(), e);
            return Optional.empty();
        }
    }


    /**
     *
     * @return
     */
    public static Optional<List<GPUInfo>> GetMttGpuInfo()
    {
       try {
           // nvidia-smi  --list-gpus
           String cmd = "mthreads-gmi -L ";
//           System.out.println("[cmd = " + cmd + "]");
           String MttGpuCountInfo = getcommand(cmd);

//           System.out.println("[GpuList = "+ MttGpuCountInfo +"]");
           List<GPUInfo> gpunames =   ParseMttGpuCountInfo(MttGpuCountInfo);
           List<GPUInfo> gpuInfos = new ArrayList<GPUInfo>();
           for(GPUInfo gpu : gpunames)
           {
               String mtt_all_info_cmd = "mthreads-gmi -q ";
               GPUInfo gpuInfo = PareseMttGpuAllInfo(getcommand(mtt_all_info_cmd));
//               System.out.println("----->>>>>>>>PareseMttGpuAllInfo>>>>>>>>>>>>>>>>>>");
               if (null != gpuInfo )
               {
//                   System.out.println("mt  gpu all info = " + gpuInfo.toString());
                   gpuInfo.setGpuIndex(gpu.getGpuIndex());
                   gpuInfo.setName(gpu.getName());
                   gpuInfos.add(gpuInfo);
               }
               else
               {
                   System.out.println(" [mt gpu all info  null !!!!]");
               }
           }
           if (gpuInfos.isEmpty())
           {
               System.out.println("MT thread -->  ---> enpty");
               return Optional.empty();
           }
//           System.out.println("Mt thread --> size = " + gpuInfos.size());
           return Optional.of(gpuInfos);
          // String gpuXmlInfo = getGpuXmlInfo();
//            String gpuarrayinfo = getcommand(cmd);
//            System.out.println(gpuXmlInfo);
//           List<GPUInfo> gpuInfos = convertXmlToGpuObject(gpuXmlInfo);
//           return Optional.of(gpuInfos);
       }
       catch (Exception e)
       {
           return Optional.empty();
       }

//        return Optional.empty();
    }



    /**
     * 获取gpu信息
     *
     * @return gpu信息集合
     */
    public static Optional<String> getGpuEncode_Decode_Info(String cmd)
    {
        try {
            String gpuXmlInfo = getcommand(cmd);
//            System.out.println(gpuXmlInfo);
//            List<GPUInfo> gpuInfos = convertXmlToGpuObject(gpuXmlInfo);
            return Optional.of(gpuXmlInfo);
        } catch (Exception e) {
//            System.out.println("获取gpu信息error , message : {}", e.getMessage(), e);
            return Optional.empty();
        }
    }
}
