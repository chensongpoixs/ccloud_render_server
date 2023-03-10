/**
 * date: 2022-10-10
 * author:chensong
 */
package com.chen.system;

import java.util.ArrayList;
import java.util.List;

public class GPUInfo
{
    private String gpuIndex;

    //名称
    private String name;
    //总内存
    private String totalMemory;
    //已用内存
    private String usedMemory;
    //空闲内存
    private String freeMemory;



    /**
     * 使用率 整形，最大为100
     */
    private int usageRate;

    //进程信息
    private List<ProcessInfo> processInfos;


    private String VideoEncode;
    private String VideoDecode;
   // private gpuVideo GpuVideo;


    public GPUInfo()
    {
        this.gpuIndex = "";
        this.name = "";
        this.totalMemory = "";
        this.usedMemory = "";
        this.freeMemory = "";
        this.usageRate = 0;
        this.processInfos = new ArrayList<ProcessInfo>();
        this.VideoEncode = "";
        this.VideoDecode = "";
    }

    public void setGpuIndex(String value)
    {
        this.gpuIndex = value;
    }

    public String getGpuIndex()
    {
        return this.gpuIndex;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getTotalMemory() {
        return totalMemory;
    }


    public void setTotalMemory(String totalMemory) {
        this.totalMemory = totalMemory;
    }

    public String getUsedMemory() {
        return usedMemory;
    }

    public void setUsedMemory(String usedMemory) {
        this.usedMemory = usedMemory;
    }

    public String getFreeMemory() {
        return freeMemory;
    }

    public void setFreeMemory(String freeMemory) {
        this.freeMemory = freeMemory;
    }

    public int getUsageRate() {
        return usageRate;
    }

    public void setUsageRate(int usageRate) {
        this.usageRate = usageRate;
    }

    public List<ProcessInfo> getProcessInfos() {
        return processInfos;
    }

    public void setProcessInfos(List<ProcessInfo> processInfos) {
        this.processInfos = processInfos;
    }



    public void setVideoDecode(String value)
    {
        this.VideoDecode = value;
    }
    public String getVideoDecode()
    {
        return this.VideoDecode;
    }
    public void setVideoEncode(String value)
    {
        this.VideoEncode = value;
    }
    public String getVideoEncode()
    {
        return  this.VideoEncode;
    }

//    public void setGpuVideo(gpuVideo value)
//    {
//        this.GpuVideo = value;
//    }
//    public gpuVideo getGpuVideo()
//    {
//        return this.GpuVideo;
//    }

    public String ToString()
    {
        return "[name = "+this.name +  "][totalMemory " + this.freeMemory + "][ usedMemory = " + this.usedMemory + "][ freeMemory = " + this.freeMemory + "][usageRate = " + this.usageRate+ "][ gpu_index = " + this.gpuIndex + "][videoEncode = "+this.VideoEncode+ "][ videoDecode = " + this.VideoDecode + "]";
    }
}
