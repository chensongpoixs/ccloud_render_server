/**
 * date: 2022-10-10
 * author:chensong
 */
package com.chen.system;

public class ProcessInfo
{
    private String pid;
    private String name;
    private String usedMemory;

    public String getPid() {
        return pid;
    }

    public void setPid(String pid) {
        this.pid = pid;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUsedMemory() {
        return usedMemory;
    }

    public void setUsedMemory(String usedMemory) {
        this.usedMemory = usedMemory;

    }
}
