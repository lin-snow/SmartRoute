@REM "Delete the app directory"

rd /s /q app

@REM "Create the app directory"

mkdir app

@REM "Delete the build directory"

rd /s /q build

@REM "Create the build directory"

mkdir build

@REM "Build the backend"

call build_backend.bat

@REM "Build the frontend"

call build_frontend.bat

@REM "Copy the frontend dist to the app directory(\app\dist)"

xcopy /s /e /y .\dist\ ..\app\dist\

@REM "Change to the root directory"

cd ..

@REM "Change to the app directory"

cd app

@REM "Run the application"

pause

.\SmartRoute.exe


