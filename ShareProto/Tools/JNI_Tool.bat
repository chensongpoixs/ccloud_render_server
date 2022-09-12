@echo off

setlocal

setlocal enabledelayedexpansion

cd /d %~dp0





javah -classpath . -jni -encoding UTF-8 cloud_game.cloud_game_mgr


pause 