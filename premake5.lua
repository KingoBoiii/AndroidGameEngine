workspace "CppAndroidTest"
	architecture "x86_64"
	startproject "App"

	configurations { 
		"Debug",
		"Release"
	}

    flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
LibraryDir = {}
Library = {}

include "Engine"
include "AndroidRuntime"
