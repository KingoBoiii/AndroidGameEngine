#pragma once

namespace Engine
{

	class Renderer
	{
	public:
		static void Initialize(void* window);

		static void Clear();
		static void ClearColor(float r, float g, float b, float a = 1.0f);

		static void Present();
	};

}
