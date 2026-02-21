@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cl test.c
if %ERRORLEVEL% equ 0 (
    echo Compilation successful! Running the program...
    test.exe
) else (
    echo Compilation failed!
)
pause