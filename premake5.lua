

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

project "02HelloDot"
    kind "ConsoleApp"
    language "C++"
    defines {"GLEW_STATIC"}
    files {"02HelloDot/**.h","02HelloDot/**.cpp"}
    includedirs {".","./common","./common/assimp"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut"}

project "03FirstTriangle"
    kind "ConsoleApp"
    language "C++"
    defines {"GLEW_STATIC"}
    files {"03FirstTriangle/**.h","03FirstTriangle/**.cpp"}
    includedirs {".","./common","./common/assimp"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut"}

project "05Uniform"
    kind "ConsoleApp"
    language "C++"
    defines {"WIN32","GLEW_STATIC"}
    files {"05Uniform/**.h","05Uniform/**.cpp","common/ogldev_util.h","common/ogldev_util.cpp"}
    includedirs {".","./common","./common/assimp"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut"}



project "11Transformations"
    kind "ConsoleApp"
    language "C++"
    defines {"WIN32","GLEW_STATIC"}
    files {
        "11Transformations/**.h",
        "11Transformations/**.cpp",
        "common/ogldev_util.h",
        "common/ogldev_util.cpp",
        "common/ogldev_pipeline.h",
        "common/ogldev_atb.h",
        "common/ogldev_atb.cpp",
        "common/pipeline.cpp",
        "common/math_3d.cpp",
        }
    includedirs {".","./common","./common/assimp"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut","AntTweakBar"}    
        

project "12PerspectiveProjection"
    kind "ConsoleApp"
    language "C++"
    defines {"WIN32","GLEW_STATIC"}
    files {
        "12PerspectiveProjection/**.h",
        "12PerspectiveProjection/**.cpp",
        "common/ogldev_util.h",
        "common/ogldev_util.cpp",
        "common/ogldev_pipeline.h",
        "common/ogldev_atb.h",
        "common/ogldev_atb.cpp",
        "common/pipeline.cpp",
        "common/math_3d.cpp",
        }
    includedirs {".","./common","./common/assimp"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut","AntTweakBar"}    
        
project "13CameraSpace"
    kind "ConsoleApp"
    language "C++"
    defines {"WIN32","GLEW_STATIC"}
    files {
        "13CameraSpace/**.h",
        "13CameraSpace/**.cpp",
        "common/ogldev_util.h",
        "common/ogldev_util.cpp",
        "common/ogldev_pipeline.h",
        "common/ogldev_atb.h",
        "common/ogldev_atb.cpp",
        "common/ogldev_keys.h",
        "common/pipeline.cpp",
        "common/math_3d.cpp",
        "common/ogldev_math_3d.h",
        "common/camera.cpp",
        }
    includedirs {".","./common","./common/assimp"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut","AntTweakBar"}    
        

project "14CameraControl"
    kind "ConsoleApp"
    language "C++"
    defines {"WIN32","GLEW_STATIC"}
    files {
        "14CameraControl/**.h",
        "14CameraControl/**.cpp",
        "common/ogldev_util.h",
        "common/ogldev_util.cpp",
        "common/ogldev_pipeline.h",
        "common/ogldev_atb.h",
        "common/ogldev_atb.cpp",
        "common/ogldev_keys.h",
        "common/pipeline.cpp",
        "common/math_3d.cpp",
        "common/ogldev_math_3d.h",
        "common/camera.cpp",
        "common/ogldev_glut_backend.h",
        "common/glut_backend.cpp",
        }
    includedirs {".","./common","./common/assimp","./freeglut"}
    implibdir "./lib"
    libdirs "./lib"
    configuration { "windows" }
        links { "GLEW", "glu32", "opengl32", "winmm" ,"freeglut","AntTweakBar"}    
        
    

             
        