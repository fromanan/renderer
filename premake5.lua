workspace "Renderer"
	architecture "x86"

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
	runtime "Release"
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

		"%{prj.name}/Renderer.rc",
		"%{prj.name}/Renderer.aps",

		"%{prj.name}/res/Renderer.ico",
		"%{prj.name}/res/Renderer.rc2",
		"%{prj.name}/res/Renderer.bmp",

		"%{prj.name}/models/*",
		"%{prj.name}/textures/*",
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
		"glu32.lib"
	}

	flags { "MFC" }

	postbuildcommands
	{
		("{COPYDIR} models ../bin/" .. outputdir .. "/%{prj.name}/models"),
		("{COPYDIR} textures ../bin/" .. outputdir .. "/%{prj.name}/textures"),
		("{COPYDIR} vendor/ShaderWnd/shaders ../bin/" .. outputdir .. "/%{prj.name}/shaders")
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines { "WIN32", "NDEBUG" }

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Dist"
		optimize "On"