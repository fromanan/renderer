workspace "Renderer"
	architecture "x86"
package.path = './?.lua;' .. package.path;
PremakeHelpers = require("PremakeHelpers");

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Renderer"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["ShaderWnd"] = "Renderer/vendor/ShaderWnd"
IncludeDir["GLM"] = "Renderer/vendor/ShaderWnd/vendor/glm"

include "Renderer/vendor/ShaderWnd"

project "Renderer"
	location "Renderer"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	entrypoint "wWinMainCRTStartup"

	pchheader "pch.h"
	pchsource "Renderer/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",

		-- Resource Files
		("%{prj.name}/res/" .. PROJECT_ROOT .. ".rc"),
		("%{prj.name}/res/" .. PROJECT_ROOT .. ".aps"),
		("%{prj.name}/res/" .. PROJECT_ROOT .. ".ico"),
		("%{prj.name}/res/" .. PROJECT_ROOT .. ".rc2"),

		("%{prj.name}/res/Toolbar.bmp"),
		("%{prj.name}/res/Toolbar256.bmp"),
		("%{prj.name}/res/UserImages.bmp"),

		-- Models / Textures
		"%{prj.name}/models/*",
		"%{prj.name}/textures/*"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.ShaderWnd}",
		"%{IncludeDir.ShaderWnd}/src"
	}

	links
	{
		"ShaderWnd",

		"opengl32.lib",
		"glu32.lib",
		"winmm.lib",

		"dwmapi.lib",
		"advapi32.lib",

		"VERSION.dll",
		"MSVCP140D.dll",
		"Mfc140d.dll",
		"KERNEL32.dll",
		"USER32.dll",
		"GDI32.dll",
		"SHELL32.dll",
		"OLEAUT32.dll",
		"VCRUNTIME140D.dll",
		"Ucrtgbased.dll",
		"WS2_32.dll"
	}

	defines
	{
		"WINDOWS_EXPORT_ALL_SYMBOLS",
		"_UNICODE"
	}

	flags { "MFC" }

	postbuildcommands
	{
		("{COPYDIR} models ../bin/" .. outputdir .. "/%{prj.name}/models"),
		("{COPYDIR} textures ../bin/" .. outputdir .. "/%{prj.name}/textures"),
		("{COPYDIR} vendor/ShaderWnd/shaders ../bin/" .. outputdir .. "/%{prj.name}/shaders")
	}

	linkoptions
	{
		"/NODEFAULTLIB:library"
	}

	filter "platforms:Win32"
		architecture "x86"

	filter "platforms:Win64"
    	architecture "x64"

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		links { "user32", "gdi32" }
		--defines { "WIN32" }

	filter "configurations:Debug"
		symbols "On"
		defines { "_DEBUG" }
		links { "msvcrtd.lib" }
		runtime "Debug"

	filter "configurations:Release"
		optimize "On"
		links { "msvcrt.lib" }
		runtime "Release"

	filter "configurations:Dist"
		optimize "On"
		links { "msvcrt.lib" }
		runtime "Release"