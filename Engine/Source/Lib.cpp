#include "Lib.h"

#ifdef PLATFORM_ANDROID
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#else
#include <iostream>
#endif

namespace Engine
{

	void Lib::print(const char* str)
	{
#ifdef PLATFORM_ANDROID
		LOGI("%s", str);
#else
	#ifdef __cplusplus
			std::cout << str << std::endl;
	#else
			printf("%s\n", str);
	#endif
#endif
	}

}