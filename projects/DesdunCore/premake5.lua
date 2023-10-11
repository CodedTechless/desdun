
project "DesdunCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir   (outputDir)
    objdir      (outputDir .. "int/")

    files { 
        "include/**.c", 
        "include/**.h",
        "include/**.cpp",
        "include/**.hpp",
        "include/**.inl", 

        "src/**.cpp",
        "src/**.hpp"
    }

    includedirs {
        "src",
        "include"
    }

    defines {
        "GLEW_STATIC" -- _CONSOLE was here but idk what it does anymore
    }

    links {
        "glfw3",
        "glew32s",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"


    filter "configurations:Debug"
        runtime "Debug"
        defines { "DEBUG" } 
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        defines { "NDEBUG" }
        optimize "On"