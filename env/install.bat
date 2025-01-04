@echo off
cd %~dp0
set CURRENT_DIR=%~dp0

dmpath.exe --addpath="%CURRENT_DIR%"
