# Java  

一般这是引入dll或者so的文件出现的，设置好java.library.path就好。

在IDEA中设置：右上角Edit Configurations→Configuration→VM options，输入下面内容：

-Djava.library.path=path_cpp_dll
 
后边跟的是dll文件的绝对路径。

在启动命令行中格式：

java -Djava.library.path=path_cpp_dll -jar  test.jar
 
 