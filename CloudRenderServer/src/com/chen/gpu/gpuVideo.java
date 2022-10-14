/**
 * date: 2022-10-10
 * author:chensong
 */
package com.chen.gpu;

public class gpuVideo
{
    private String videoEncode;

    private String videoDecode;
    public gpuVideo()
    {
        super();
         this.videoDecode = "";
         this.videoEncode = "";
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

    public String ToString()
    {
        return "[encode = "+this.videoEncode+"][ video decode = " + this.videoDecode + "]";
    }
}
