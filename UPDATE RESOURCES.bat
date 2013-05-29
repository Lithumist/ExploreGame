:: 
:: This script updates the /res folder in all builds, except the deployable one! (in /build folder)
:: Resources/res is the master
:: 

@echo on

cd "Release"
del /f /q "Irrlicht.dll"
cd "../"
cd "Debug"
del /f /q "Irrlicht.dll"
cd "../"
cd "ExploreGameEngine"
del /f /q "Irrlicht.dll"
cd "../"

rmdir /s /q "Release/res"
rmdir /s /q "Debug/res"
rmdir /s /q "ExploreGameEngine/res"

xcopy "Resources" "Release" /s /e /v
xcopy "Resources" "Debug" /s /e /v
xcopy "Resources" "ExploreGameEngine" /s /e /v