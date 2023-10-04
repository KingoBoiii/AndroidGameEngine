project "AndroidRuntime"
	kind "Utility"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	--architecture "x86_64"
	--system "android"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.cpp",
		"Source/**.h",
	}

	prebuildcommands {
		"G:/AndroidStudio/SDK/ndk/25.1.8937393/build/ndk-build.cmd -C G:/Tests/CppAndroidTest/AndroidRuntime/Source"
	}
	
	includedirs {
		"%{wks.location}/App/Source",
		"%{wks.location}/Engine/Source",
		--"G:/AndroidStudio/SDK/ndk/25.1.8937393/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include", -- only if Android Studio NDK is installed!
		"G:/AndroidStudio/SDK/ndk/25.1.8937393/sources/android/native_app_glue"
	}

	defines {
		"PLATFORM_ANDROID"
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


