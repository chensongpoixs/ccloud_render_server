package com.chen.system;

public class CpuInfo
{
    public CpuInfo ()
    {
        super();
       this. m_date_time = "";
       this. m_cpu_precent = "";
    }

    public CpuInfo(String m_date_time, String m_cpu_precent)
    {
        this.m_date_time = m_date_time;
        this.m_cpu_precent = m_cpu_precent;
    }

    @Override
    public String toString() {
        return "CpuInfo{" +
                "m_date_time='" + m_date_time + '\'' +
                ", m_cpu_precent='" + m_cpu_precent + '\'' +
                '}';
    }

    public String GetDateTime()
    {
        return m_date_time;
    }

    public String GetCpuPercentage()
    {
        return m_cpu_precent;
    }

    public void setM_date_time(String m_date_time)
    {
        this.m_date_time = m_date_time;
    }

    public void setM_cpu_precent(String m_cpu_precent)
    {
        this.m_cpu_precent = m_cpu_precent;
    }

    private String m_date_time;
    private String m_cpu_precent;
}
