@REM cd web

@REM xcopy /s /e /y dist ..\app\

@REM pause

@REM cd app

@REM .\SmartRoute.exe

rd /s /q app
mkdir app

echo Running backend build...
call ./build_backend.bat
if %errorlevel% neq 0 (
    echo "Backend build failed, exiting..."
    pause
    exit /b %errorlevel%
)

echo Running frontend build...
call ./build_frontend.bat
if %errorlevel% neq 0 (
    echo "Frontend build failed, exiting..."
    pause
    exit /b %errorlevel%
)

echo Checking if dist directory exists...
if not exist dist (
    echo "dist directory not found!"
    pause
    exit /b
)

echo Copying frontend files...
xcopy /s /e /y dist ..\app\dist

echo Changing to app directory...
cd app
if not exist SmartRoute.exe (
    echo "SmartRoute.exe not found in app directory!"
    pause
    exit /b
)

echo Running SmartRoute.exe...
.\SmartRoute.exe