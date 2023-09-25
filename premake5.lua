workspace "Renderer"
	architecture "x86"

PROJECT_ROOT = "Renderer";

-- Include directories relative to root folder (solution directory)
IncludeDir = {
	ShaderWnd = PROJECT_ROOT .. "/vendor/ShaderWnd"
};

workspace (PROJECT_ROOT)
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	startproject (PROJECT_ROOT)

include "Renderer/vendor/ShaderWnd"

project (PROJECT_ROOT)
	location (PROJECT_ROOT)
	kind "ConsoleApp"
	language "C++"
	runtime "Release"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	entrypoint "wWinMainCRTStartup"

	pchheader ("pch.h")
	pchsource (PROJECT_ROOT .. "/src/pch.cpp")

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

		("%{prj.name}/res/Toolbar256.bmp"),
		("%{prj.name}/res/UserImages.bmp"),
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