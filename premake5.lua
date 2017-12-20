

workspace "OpenglStep"
    location ("Build/%{_ACTION}")
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

project "GLEW"
    kind "StaticLib"
    language "C++"
    defines { "GLEW_STATIC" }
    files { "glew/*.h", "glew/*.c" }
    includedirs { "." }

-- 还有问题
-- project "freeglut"
--     kind "StaticLib"
--     language "C++"
--     files { "freeglut/src/**.h", "freeglut/src/*.c" ,"freeglut/src/mswin/*.c","freeglut/GL/*.h"}
--     includedirs { "./freeglut","./freeglut/src" }

project "01TestCon"
    kind "ConsoleApp"
    language "C++"
    defines {"GLEW_STATIC"}
    files {"01TestCon/**.h","01TestCon/**.cpp"}
    includedirs {"."}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut"}