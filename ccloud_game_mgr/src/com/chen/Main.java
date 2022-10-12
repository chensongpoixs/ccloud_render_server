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
        if (args.length != 5)
        {
            System.out.println(" argc != 5, cmd: server_name wan_port  g_thrift_server_ip  thrift_server_port   g_thrift_client_port  [argc ="+ args.length + "]");
            return;
        }

        System.out.println(System.getProperty("java.library.path"));


//        //String server_name, int wan_port, String thrift_server_host, int thrift_server_port, int thrift_client_port
        boolean init = cloud_game_mgr.cloudrenderinit(args[0], Integer.parseInt(args[1]), args[2],Integer.parseInt( args[3]), Integer.parseInt(args[4]));


        if (init)
        {

           init =        cloud_game_mgr.cloudrenderloop();


        }



//        while (true)
//        {
//            try {
//
//                Thread.sleep(1000);
//                System.out.println("sleep 100");
//            } catch (Exception e) {
//                e.printStackTrace();
//               System.out.println( "Exception");
//
//            }
//        }
        cloud_game_mgr.cloudrenderdestroy();;






//        System.get
//        cloud_game_mgr c = new cloud_game_mgr();
//        cloud_game_mgr.nativeMethod();;
//        Optional<List<GPUInfo>> gpu_infos =  SystemGpu.getGpuInfo();
//        if (null != gpu_infos)
//        {
//            c.Gpuinfo(gpu_infos.get());
//        }

//        c.nativeMethod();

    }
}
