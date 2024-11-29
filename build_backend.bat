@REM "Change to the build directory"

cd build

@REM "Run CMake"

cmake -G "MinGW Makefiles" ..

@REM "Run Make"

mingw32-make

@REM "Copy the executable to the app directory"

copy /y SmartRoute.exe ..\app\

@REM "Copy the data directory to the app directory"

xcopy /s /e /y .\data\ ..\app\data\

@REM "Copy the config directory to the app directory"

xcopy /s /e /y .\config\ ..\app\config\

@REM "Change to the root directory"

cd ..