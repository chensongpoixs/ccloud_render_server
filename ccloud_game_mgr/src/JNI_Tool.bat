@echo off

setlocal

setlocal enabledelayedexpansion

cd /d %~dp0





"C:\Program Files\Java\jdk1.8.0_181\bin\javah.exe" -classpath . -jni -encoding UTF-8 com.chen.cloud.cloud_game_mgr


pause 