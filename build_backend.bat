rd /s /q app

mkdir app

rd /s /q build

mkdir build

cd build

cmake -G "MinGW Makefiles" ..

mingw32-make

copy /y SmartRoute.exe ..\app

xcopy /s /e /y \data ..\app\data

xcopy /s /e /y \config ..\app\config

cd ..