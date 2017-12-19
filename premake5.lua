

workspace "OpenglStep"
    location ("Build/%{_ACTION}")
    architecture "x86_64"
    configurations { "Debug", "Release" }

    configuration "vs*"
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        targetdir ( "Build/%{_ACTION}/bin/Debug" )
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        targetdir ( "Build/%{_ACTION}/bin/Release" )
        defines { "NDEBUG" }
        optimize "On"

project "freeglut"
    kind "StaticLib"
    language "C++"
    files { "freeglut/src/**.h", "freeglut/src/*.c" ,"freeglut/src/mswin/*.c","freeglut/GL/*.h"}
    includedirs { "./freeglut","./freeglut/src" }