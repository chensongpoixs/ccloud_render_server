package com.company;

public class Main {

    static {
        System.loadLibrary("cloud_game");
    }
    public static native boolean CloudRenderLoop();
    public static void main(String[] args)
    {
        System.out.println("Loop --> C++ !!!");
	// write your code here
        CloudRenderLoop();
        System.out.println("Loop exit java !!!");
    }
}
