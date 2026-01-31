#pragma once

#include <cstdint>
#include <stdlib.h>
#include <iostream>

#include "SDL3/SDL.h"
#include "Primitives/Rectangle.h"
#include "Primitives/Triangle.h"
#include "Defs.h"

namespace eng
{

	enum Color
	{
		Red = 0xffff'0000,
		Green = 0xff00'ff00,
		Blue = 0xff00'00ff,
	};

	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void init(SDL_Renderer* renderer, int windowWidth, int windowHeight);

		Color_t createColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		//------------------------//
		void drawGrid(size_t gx, size_t gy, Color_t Color);
		void drawDots(size_t gx, size_t gy, Color_t Color);
		//------------------------//


		void clearColorBuffer(Color_t color);
		void drawColorBuffer();

		void drawPixel(int x, int y, Color_t color);
		void drawLine(int x0, int y0, int x1, int y1, Color_t color);

		void drawTriangle(eng::Triangle& triangle, Color_t color);

		void drawFilledRectangle(eng::Rectangle& rect, Color_t color);
		void drawRectangle(eng::Rectangle& rect, Color_t color);
		void drawCircle();

		void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color_t color);

		void drawFilledTriangle(eng::Triangle& trig, Color_t color);

	private:

		void fillFlatBottomTriangle();
		void fillFlatTopTriangle();

		void ddaLineAlgo(int x0, int y0, int x1, int y1, Color_t color);

		uint32_t* m_colorBuffer;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_canvas;

		int m_cwindowWidth;
		int m_cwindowHeight;
	};


}