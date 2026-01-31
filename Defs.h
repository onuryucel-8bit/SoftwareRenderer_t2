#pragma once

#include <cstdint>
namespace eng
{
	using Color_t = uint32_t;

	struct RenderContext
	{
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* canvas;

		eng::Color_t* colorBuffer;

		//TODO make it resizable
		const int WindowWidth = 1600;
		const int WindowHeight = 800;
	};
}