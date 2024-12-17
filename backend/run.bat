@echo off 
cd /D %~dp0
cd build
COPY /Y ..\backend.config .
COPY /Y/B ..\ATRC\libs\win\*.dll .
COPY /Y/B ..\libs\*.dll .
call cpp-backend-server.exe
echo %ERRORLEVEL%
