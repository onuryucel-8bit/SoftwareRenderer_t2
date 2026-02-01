#pragma once

#include <cstdint>
#include <iostream>
#include <chrono>

#include "SDL3/SDL.h"
#include "Graphics.h"

#include "Primitives/Triangle.h"
#include "Primitives/Rectangle.h"
#include "Defs.h"

#include "utils/Timer.h"

namespace eng
{	
	class Application
	{
	public:
		Application();
		~Application();

		void run();

	private:
		void initWindow();
		void update(float dt);
		void input(SDL_Event& event);
		void draw();
		void setup();

		float test_varx = 0.0f;
		float test_vary = 0.0f;
		float t = 0.0f;
		Color_t test_color;

		eng::Graphics gp;

		bool f_running;

		eng::RenderContext m_context;
	};

}