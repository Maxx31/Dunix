workspace "Dunix"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Dunix"
	location "Dunix"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	 buildoptions 
	 {
        "/utf-8"
     }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines
		{
			"DX_PLATFORM_WINDOWS",
			"DX_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "DX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DX_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Dunix/vendor/spdlog/include",
		"Dunix/src"
	}

	links
	{
		"Dunix"
	}

	buildoptions 
	 {
        "/utf-8"
     }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22621.0"

		defines
		{
			"DX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DX_DIST"
		optimize "On"