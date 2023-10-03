project "AndroidRuntime"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.cpp",
		"Source/**.h",
	}
	
	includedirs {
		"%{wks.location}/App/Source",
		"%{wks.location}/Engine/Source",
		"G:/AndroidStudio/SDK/ndk/25.1.8937393/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include", -- only if Android Studio NDK is installed!
		"G:/AndroidStudio/SDK/ndk/25.1.8937393/sources/android/native_app_glue"
	}

	links {
		"Engine"
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