@echo off

setlocal

setlocal enabledelayedexpansion

cd /d %~dp0





javah.exe -classpath . -jni -encoding UTF-8 com.chen.cloud.CloudRenderServer


pause 