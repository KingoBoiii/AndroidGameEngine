#include "Renderer.h"

#ifdef PLATFORM_ANDROID
#include "EGL/egl.h"
#include "GLES3/gl3.h"

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#endif

#include <memory>
#include <cassert>

#include "Lib.h"

namespace Engine
{

	struct RendererData
	{
#ifdef PLATFORM_ANDROID 
		EGLDisplay Display;
		EGLSurface Surface;
		EGLContext Context;
#endif

		int32_t Width;
		int32_t Height;
	};
	static RendererData* s_Data = nullptr;

	void Renderer::Initialize(void* window)
	{
		s_Data = new RendererData();
#ifdef PLATFORM_ANDROID
		const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
		};

		EGLint w, h, format;
		EGLint numConfigs;
		EGLConfig config = nullptr;
		EGLSurface surface = nullptr;
		EGLContext context = nullptr;
		EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		eglInitialize(display, nullptr, nullptr);

		/* Here, the application chooses the configuration it desires.
		* find the best match if possible, otherwise use the very first one
		*/
		eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);
		std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
		assert(supportedConfigs);
		eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
		assert(numConfigs);
		auto i = 0;
		for (; i < numConfigs; i++)
		{
			auto& cfg = supportedConfigs[i];
			EGLint r, g, b, d;
			if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r) &&
				eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
				eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b) &&
				eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
				r == 8 && g == 8 && b == 8 && d == 0)
			{

				config = supportedConfigs[i];
				break;
			}
		}
		if (i == numConfigs)
		{
			config = supportedConfigs[0];
		}

		if (config == nullptr)
		{
			LOGW("Unable to initialize EGLConfig");
			return;
		}

		LOGI("Initialized EGLConfig");

		/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
		 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
		 * As soon as we picked a EGLConfig, we can safely reconfigure the
		 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
		surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)window, nullptr);
		context = eglCreateContext(display, config, nullptr, nullptr);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
		{
			LOGW("Unable to eglMakeCurrent");
		}

		LOGI("eglMakeCurrent success");

		eglQuerySurface(display, surface, EGL_WIDTH, &w);
		eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		s_Data->Display = display;
		s_Data->Surface = surface;
		s_Data->Context = context;
		s_Data->Width = w;
		s_Data->Height = w;

		// Check openGL on the system
		auto opengl_info = { GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS };
		for (auto name : opengl_info)
		{
			auto info = glGetString(name);
			LOGI("OpenGL Info: %s", info);
		}

		// Initialize GL state.
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
#endif
	}

	void Renderer::Clear()
	{
#ifdef PLATFORM_ANDROID
		if (!s_Data->Display)
		{
			return;
		}

		glClear(GL_COLOR_BUFFER_BIT);
#endif
	}

	void Renderer::ClearColor(float r, float g, float b, float a)
	{
#ifdef PLATFORM_ANDROID
		if (!s_Data->Display)
		{
			return;
		}

		glClearColor(r, g, b, a);
#endif
	}

	void Renderer::Present()
	{
#ifdef PLATFORM_ANDROID
		if (!s_Data->Display || !s_Data->Surface)
		{
			return;
		}

		eglSwapBuffers(s_Data->Display, s_Data->Surface);
#endif
	}

}

