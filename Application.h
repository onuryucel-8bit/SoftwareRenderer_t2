#pragma once

#include <cstdint>
#include <iostream>

#include "SDL3/SDL.h"
#include "Graphics.h"
#include "Triangle.h"
#include "Rectangle.h"

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
		void update();
		void input(SDL_Event& event);
		void draw();
		void setup();

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		float test_var = 0;

		eng::Triangle a;
		eng::Triangle b;

		//eng::Rectangle rect;

		eng::Graphics gp;

		bool f_running;

		const int WINDOW_WIDTH = 320;
		const int WINDOW_HEIGHT = 200;
	};

}