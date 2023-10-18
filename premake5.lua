
workspace "ProjectDesdun"
    architecture "x64"
    startproject "projects/DesdunRuntime"

    platforms {
        "Win64"
    }

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

    libdirs {
        "dependencies/*"
    }

    filter "action:vs*"
        buildoptions { "/bigobj" }

outputDir = "%{wks.location}/bin/%{prj.name}/%{cfg.platform}/%{cfg.buildcfg}/"

group "Core"
    include "projects/DesdunCore"
group ""

group "Software"
    include "projects/DesdunRuntime"
    include "projects/DesdunEditor"
group ""
