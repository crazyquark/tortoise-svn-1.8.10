@echo off
setlocal

if %1x==x goto usage
set lang=%1
for %%i in (%lang%\*.png) do call :check en %%~nxi
goto :eof

:usage
echo Usage: list_missing_images language
echo This script lists all english images that are absent for 'language'
echo Example: list_missing_images fi
goto :eof

:check
if not exist %1\%2 echo %2
goto :eof
