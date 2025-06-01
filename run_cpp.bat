@echo off
setlocal enabledelayedexpansion

if "%1"=="" (
    echo Usage: run_cpp ^<cpp_file^>
    exit /b 1
)

set source_file=%1
set executable=%~n1.exe

if not exist "%source_file%" (
    echo Error: Source file '%source_file%' not found
    exit /b 1
)

echo Compiling %source_file%...
g++ -Wall -O2 "%source_file%" -o "%executable%"

if %errorlevel% equ 0 (
    echo Compilation successful. Running the program...
    echo ----------------------------------------
    "%executable%"
    set exit_code=%errorlevel%
    echo ----------------------------------------
    echo Program finished with exit code: !exit_code!
    del "%executable%"
) else (
    echo Compilation failed!
    exit /b 1
)

endlocal