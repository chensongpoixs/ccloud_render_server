/**
 *  author : chensong
 *  date : 20220912
 */

package com.chen;

import com.chen.cloud.CloudRenderServer;
import com.chen.log.Logger;
import com.chen.system.Util;
import sun.misc.Signal;
import sun.misc.SignalHandler;

//import static com.chen.cloud.cloud_game_mgr.Gpuinfo;

public class Main   implements  SignalHandler {

    private static final Logger logger = Logger.getLogger(Main.class);
    public static void main(String[] args) throws InterruptedException
    {
        if (args.length != 5)
        {
            System.out.println(" argc != 5, cmd: server_name wan_port  g_thrift_server_ip  thrift_server_port   g_thrift_client_port  [argc ="+ args.length + "]");
            return;
        }

        Main testSignalHandler = new Main();

        Signal.handle(new Signal("INT"), testSignalHandler);
        Signal.handle(new Signal("TERM"), testSignalHandler);

        boolean init = CloudRenderServer.CloudRenderInit(args[0], Integer.parseInt(args[1]), args[2],Integer.parseInt( args[3]), Integer.parseInt(args[4]));

        if (init)
        {
           init =        CloudRenderServer.CloudRenderLoop();
        }

        CloudRenderServer.CloudRenderDestory();;

    }

    @Override
    public void handle(Signal sig)
    {
        System.out.println("Signal......");
        CloudRenderServer.CloudRenderStop();;

    }
}
