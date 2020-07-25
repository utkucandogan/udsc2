include "premake5_workspace_files.lua"

workspace "udsc2"
    startproject "tests"

    workspace_files {
		".gitignore",
        "premake5.lua",
        "premake5_workspace_files.lua",
        "tests.runsettings",
    }

    configurations {
        "Debug-Static",
        "Debug-Shared",
        "Release-Static",
        "Release-Shared",
    }

    platforms {
        "Windows-x32",
        "Windows-x64",
    }

    filter "platforms:*-x32"
        architecture "x32"

    filter "platforms:*-x64"
        architecture "x64"

    filter "platforms:Windows-*"
        system "windows"

outputdir = "%{cfg.buildcfg}-%{cfg.platform}"

project "udsc2"
    location "%{prj.name}"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{outputdir}/%{prj.name}"
    objdir "int/%{outputdir}/%{prj.name}"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",

        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.hpp",
    }

    includedirs {
        "%{prj.name}/include",
        "%{prj.name}/src",
    }

    defines "UDSC2_BUILD"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug-*"
        defines "UDSC2_DEBUG"
        symbols "On"

    filter "configurations:Release-*"
        defines "UDSC2_RELEASE"
        optimize "On"

    filter "configurations:*-Static"
        kind "StaticLib"

    filter "configurations:*-Shared"
        kind "SharedLib"
        defines "UDSC2_SHARED"

    filter "toolset:msc-*"
        buildoptions {
            "/Zc:__cplusplus",
		}

project "tests"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{outputdir}/%{prj.name}"
    objdir "int/%{outputdir}/%{prj.name}"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor",
        "udsc2/include",
    }

    links {
        "udsc2"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug-*"
        defines "UDSC2_DEBUG"
        symbols "On"

    filter "configurations:Release-*"
        defines "UDSC2_RELEASE"
        optimize "On"

    filter "configurations:*-Static"
        includedirs {
            "udsc2/src",
        }

    filter "configurations:*-Shared"
        defines "UDSC2_SHARED"

    filter "toolset:msc-*"
        buildoptions {
            "/Zc:__cplusplus",
		}

project "sandbox"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{outputdir}/%{prj.name}"
    objdir "int/%{outputdir}/%{prj.name}"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/src",
        "udsc2/include",
    }

    links {
        "udsc2",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug-*"
        defines "UDSC2_DEBUG"
        symbols "On"

    filter "configurations:Release-*"
        defines "UDSC2_RELEASE"
        optimize "On"

    filter "toolset:msc-*"
        buildoptions {
            "/Zc:__cplusplus",
		}

-- Clean Function --
newaction
{
   trigger     = "clean",
   description = "clean the binaries and intermediates.",
   execute     = function ()
      os.rmdir("./bin")
      os.rmdir("./int")
      print("Done.")
   end
}
