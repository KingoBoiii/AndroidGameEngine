project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.cpp",
		"Source/**.c",
		"Source/**.h"
	}
	
	includedirs {
		"Source",
		"G:/AndroidStudio/SDK/ndk/25.1.8937393/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include" -- only if Android Studio NDK is installed!
	}
	
	links {
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "_DEBUG_"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_RELEASE_"
		runtime "Release"
		optimize "on"