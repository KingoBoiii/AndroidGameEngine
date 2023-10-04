#include <android_native_app_glue.h>
#include <jni.h>

#include <Engine.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

extern "C" {

    struct AndroidRuntime {
        bool WindowInitialized = false;
    };

    void handle_cmd(android_app* app, int32_t cmd)
    {
        auto* runtime = (struct AndroidRuntime*)app->userData;
        Engine::Lib::print("Hello World!");

        switch (cmd) {
            case APP_CMD_INIT_WINDOW:
                Engine::Renderer::Initialize(app->window);

                runtime->WindowInitialized = true;
                break;
        }
    }

    void android_main(struct android_app* app)
    {
        struct AndroidRuntime runtime{};
        app->userData = &runtime;
        app->onAppCmd = handle_cmd;

        int events;
        android_poll_source* source;
        do
        {
            if (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0)
            {
                if (source)
                {
                    source->process(app, source);
                }
            }

            if(runtime.WindowInitialized) {
                Engine::Renderer::Clear();
                Engine::Renderer::ClearColor(0.2f, 0.5f, 0.8f, 1.0f);
                Engine::Renderer::Present();
            }
        }
        while (!app->destroyRequested);
    }

}