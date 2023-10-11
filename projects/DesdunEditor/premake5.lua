
project "DesdunEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir   (outputDir)
    objdir      (outputDir .. "int/")

    files {
        "src/**.cpp",
        "src/**.hpp"
    }

    includedirs {
        "%{wks.location}/projects/DesdunCore/include",
        "%{wks.location}/projects/DesdunCore/src",
        "src"
    }

    libdirs { 
        "%{wks.location}/bin/DesdunCore/%{cfg.platform}/%{cfg.buildcfg}"
    }
    
    links {
        "DesdunCore.lib"
    }

    defines {
        "GLEW_STATIC" -- _CONSOLE was here but idk what it does anymore
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