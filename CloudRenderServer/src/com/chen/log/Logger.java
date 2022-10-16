package com.chen.log;

/**
 * date: 2022-10-16
 * author:chensong
 */
public class Logger {

    private static Logger logger = new Logger();

    public Logger() {
        super();
    }

    public static Logger getLogger(String name) {
        synchronized (Logger.class) {
            if (logger != null) {
                return logger;
            }
        }
        return null;
        //  }
        //ILoggerFactory iLoggerFactory = getILoggerFactory();
//        return iLoggerFactory.getLogger(name);
    }

    public void info(String format )
    {
        System.out.println(format);
    }
    public void info(String format, Object arg1 )
    {
        System.out.println(format+ arg1);
    }

    public void info(String format, Object arg1, Object arg2)
    {
        System.out.println(format+ arg1 + arg2);
        //this.filterAndLog_2(FQCN, (Marker)null, Level.INFO, format, arg1, arg2, (Throwable)null);
    }
    public void info(String format, Object... argArray)
    {
        System.out.println(format + argArray);
//        this.filterAndLog_0_Or3Plus(FQCN, (Marker)null, Level.INFO, format, argArray, (Throwable)null);
    }
    public static Logger getLogger(Class<?> clazz) {
        Logger logger = getLogger(clazz.getName());
        return logger;
    }
}

