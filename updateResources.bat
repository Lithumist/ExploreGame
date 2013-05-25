@echo on

rmdir /s /q "Release/res"
rmdir /s /q "Debug/res"
rmdir /s /q "ExploreGameEngine/res"

xcopy "Resources" "Release" /s /e /v
xcopy "Resources" "Debug" /s /e /v
xcopy "Resources" "ExploreGameEngine" /s /e /v