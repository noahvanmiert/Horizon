workspace "Horizon"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories relative to root folder (Solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Horizon/vendor/GLFW/include"
IncludeDir["Glad"] = "Horizon/vendor/Glad/include"
IncludeDir["ImGui"] = "Horizon/vendor/imgui"
IncludeDir["glm"] = "Horizon/vendor/glm"
IncludeDir["stb_image"] = "Horizon/vendor/stb_image"

group "Dependencies"
	include "Horizon/vendor/GLFW"
	include "Horizon/vendor/Glad"
	include "Horizon/vendor/imgui"

group ""

project "Horizon"
	location "Horizon"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hrpch.h"
	pchsource "Horizon/src/hrpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"Dwmapi.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"HR_PLATFORM_WINDOWS",
			"HR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HR_DEBUG"
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "HR_Release"
		optimize "on"
		runtime "Release"

	filter "configurations:Dist"
		defines "HR_DIST"
		optimize "on"
		runtime "Release"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs 
	{
		"Horizon/vendor/spdlog/include",
		"Horizon/src",
		"Horizon/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Horizon"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"HR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HR_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "HR_Release"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "HR_DIST"
		optimize "On"
		runtime "Release"
