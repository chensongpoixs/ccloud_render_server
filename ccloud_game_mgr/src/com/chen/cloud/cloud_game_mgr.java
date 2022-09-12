package com.chen.cloud;

public class cloud_game_mgr
{
    static
    {

        System.loadLibrary("cloud_game");
    }
    public native void nativeMethod();

    public static  void callback()
    {
        System.out.println("In Java");
    }


}
