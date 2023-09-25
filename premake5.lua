package.path = './?.lua;' .. package.path;
PremakeHelpers = require("PremakeHelpers");

outputdir = PremakeHelpers.OutputDirectory;

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

	platforms
	{
		"Win32",
		"Win64"
	}

	startproject (PROJECT_ROOT)

include (IncludeDir.ShaderWnd)

project (PROJECT_ROOT)
	location (PROJECT_ROOT)
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	entrypoint ("wWinMainCRTStartup")

	pchheader ("pch.h")
	pchsource (PROJECT_ROOT .. "/src/pch.cpp")

	files
	{
		-- Source Files
		PremakeHelpers.IncludeCHeaders,
		PremakeHelpers.IncludeCPPHeaders,
		PremakeHelpers.IncludeCPPSources,

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
		"%{IncludeDir.ShaderWnd}/src",

		"%{IncludeDir.ShaderWnd}/shaders",
		"%{IncludeDir.ShaderWnd}/vendor/glm",
		"%{IncludeDir.ShaderWnd}/vendor/glm/gtc",
		"%{IncludeDir.ShaderWnd}/vendor/glew-1.9.0/include/GL"
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
		PremakeHelpers.CopyToOutput("models"),
		PremakeHelpers.CopyToOutput("textures"),
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