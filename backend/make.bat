@ECHO OFF
SETLOCAL

SET "MSVS_PATH=%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
IF EXIST "%MSVS_PATH%" CALL "%MSVS_PATH%"

cd /D %~dp0
if not exist build mkdir build
cd build
cmake .. -G "Ninja"
cmake --build .

ENDLOCAL