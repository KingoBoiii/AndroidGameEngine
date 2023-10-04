local os = require("os")
androidNDK = os.getenv("ANDROID_NDK_PATH");

if(androidNDK == nil) then
	print("Android NDK path has not been set in System Environment variables!")
	os.exit()
end

print(androidNDK)

project "AndroidRuntime"
	kind "Utility"
	language "C++"
	-- cppdialect "C++17"
	-- staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.cpp",
		"Source/**.h",
	}

	prebuildcommands {
		"%{androidNDK}/build/ndk-build.cmd -C %{wks.location}/AndroidRuntime/Source"
	}
	
	externalincludedirs {
		"%{wks.location}/App/Source",
		"%{wks.location}/Engine/Source",
		"%{androidNDK}/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include",
		"%{androidNDK}/sources/android/native_app_glue"
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


