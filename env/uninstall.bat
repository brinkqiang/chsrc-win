@echo off
cd %~dp0
set CURRENT_DIR=%~dp0
rem Remove the path from the system
dmpath.exe --removepath="%CURRENT_DIR%"
