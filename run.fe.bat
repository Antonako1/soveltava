@ECHO OFF
SETLOCAL
CD /D %~dp0
CD frontend
IF NOT EXIST node_modules call npm i
call npm run dev
ENDLOCAL