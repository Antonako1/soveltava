@ECHO OFF
SET "ERROR_MSG=Error: "
SET "ERROR_LEVEL=0"
SETLOCAL

CD /D %~dp0
cd backend

call make.bat
if %ERRORLEVEL% neq 0 (
    SET "ERROR_MSG=Error: make.bat failed"
    SET "ERROR_LEVEL=1"
    GOTO ERROR
)
call run.bat

ENDLOCAL
EXIT /B %ERROR_LEVEL%

:ERROR
ECHO %ERROR_MSG%
ENDLOCAL
EXIT /B %ERROR_LEVEL%
