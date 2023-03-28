/**
 * date: 2022-10-10
 * author:chensong
 */
package com.chen.system;

public class gpuVideo
{
    private String videoEncode;

    private String videoDecode;

    private String Gpu;
    public gpuVideo()
    {

         this.videoDecode = "";
         this.videoEncode = "";
         this.Gpu = "";
    }
    public void setVideoEncode(String value)
    {
        this.videoEncode = value;
    }

    public String getVideoEncode()
    {
        return this.videoEncode;
    }

    public void setVideoDecode(String value)
    {
        this.videoDecode = value;
    }

    public String getVideoDecode()
    {
        return this.videoDecode;
    }

    public String getGpu() {
        return Gpu;
    }

    public void setGpu(String gpu) {
        Gpu = gpu;
    }

    @Override
    public String toString() {
        return "gpuVideo{" +
                "videoEncode='" + this.videoEncode + '\'' +
                ", videoDecode='" + this.videoDecode + '\'' +
                ", Gpu='" + this.Gpu + '\'' +
                '}';
    }
}
