:: 
:: This script gets a build of the game from the 'Release' folder and
:: uses it to make a deployable build of the game to distribute
:: 





:: Remove old build
rmdir /s /q "Build/Game"

:: Copy the new build over
echo d | xcopy "Release" "Build/Game" /s /e /v

:: Copy the vc++2010 redist dlls
echo d | xcopy "redist" "Build/Game" /s /e /v

:: Delete unnecessary files
cd "Build/Game"
del "log.txt"
del "ExploreGameEngine.pdb"

:: Rename game executable
ren "ExploreGameEngine.exe" "Explore Game.exe"

pause