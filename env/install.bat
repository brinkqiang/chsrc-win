@echo off
cd %~dp0
set CURRENT_DIR=%~dp0
rem Add the path to the system
dmpath.exe --addpath="%CURRENT_DIR%"
