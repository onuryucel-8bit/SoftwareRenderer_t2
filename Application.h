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

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		eng::Graphics gp;

		bool f_running;

		const int WINDOW_WIDTH = 320;
		const int WINDOW_HEIGHT = 200;
	};

}