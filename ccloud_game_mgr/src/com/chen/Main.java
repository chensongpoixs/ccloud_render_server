/**
 *  author : chensong
 *  date : 20220912
 */

package com.chen;

import com.chen.cloud.cloud_game_mgr;
import com.chen.gpu.GPUInfo;
import com.chen.gpu.SystemGpu;
import com.chen.whindow.ChineseChessMainFrame;

import java.util.List;
import java.util.Optional;

public class Main {

    public static void main(String[] args)
    {


        System.out.println(System.getProperty("java.library.path"));
        cloud_game_mgr c = new cloud_game_mgr();
        Optional<List<GPUInfo>> gpu_infos =  SystemGpu.getGpuInfo();
        if (null != gpu_infos)
        {
            c.Gpuinfo(gpu_infos.get());
        }

        c.nativeMethod();

    }
}
