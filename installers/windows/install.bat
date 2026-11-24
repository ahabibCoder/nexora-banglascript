@echo off
setlocal
echo ========================================================
echo    Installing BanglaScript to Windows User Environment
echo ========================================================
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0install.ps1"
pause
