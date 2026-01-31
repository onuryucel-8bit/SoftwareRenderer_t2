#include "Graphics.h"

namespace eng
{

	Graphics::Graphics()
		:m_renderer(nullptr),
		m_canvas(nullptr),
		m_colorBuffer(nullptr),
		m_cwindowWidth(0),
		m_cwindowHeight(0)
	{
	}

	Graphics::~Graphics()
	{
		free(m_colorBuffer);
		SDL_DestroyTexture(m_canvas);
	}

	void Graphics::init(SDL_Renderer* renderer, int windowWidth, int windowHeight)
	{
		m_renderer = renderer;
		m_cwindowWidth = windowWidth;
		m_cwindowHeight = windowHeight;

		m_colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);

		if (m_colorBuffer == NULL)
		{
			std::cout << "Error:: ColorBuffer initializing failed\n";
			//return false;
		}

		m_canvas = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_cwindowWidth, m_cwindowHeight);

		if (m_canvas == NULL)
		{
			std::cout << "Error:: Texture initializing failed\n";
			//return false;
		}
	}

	Color_t Graphics::createColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		Color_t color = a;
		color <<= 3 * 8;

		Color_t red = r;
		color = (red << 2 * 8) | color;

		Color_t blue = b;
		color = (blue << 1 * 8) | color;

		Color_t green = g;
		color = green | color;

		return color;

	}

	void Graphics::drawGrid(size_t gx, size_t gy, Color_t Color)
	{
		for (size_t y = 0; y < m_cwindowHeight; y++)
		{
			for (size_t x = 0; x < m_cwindowWidth; x++)
			{
				if (x % gx == 0 || y % gy == 0)
				{
					drawPixel(x, y, Color);
				}
			}
		}
	}

	void Graphics::drawDots(size_t gx, size_t gy, Color_t Color)
	{
		for (size_t y = 0; y < m_cwindowHeight; y += 40)
		{
			for (size_t x = 0; x < m_cwindowWidth; x += 40)
			{
				drawPixel(x, y, Color);
			}
		}
	}

	void Graphics::clearColorBuffer(Color_t color)
	{
		for (size_t i = 0; i < m_cwindowWidth * m_cwindowHeight; i++)
		{
			m_colorBuffer[i] = color;
		}
	}

	void Graphics::drawColorBuffer()
	{
		//load colorbuffer
		SDL_UpdateTexture(m_canvas, NULL, m_colorBuffer, (int)(m_cwindowWidth * sizeof(uint32_t)));

		//make it pixaled
		SDL_SetTextureScaleMode(m_canvas, SDL_SCALEMODE_NEAREST);

		//render canvas
		SDL_RenderTexture(m_renderer, m_canvas, NULL, NULL);

		//swap buffers
		SDL_RenderPresent(m_renderer);
	}


	//------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------//
	//------------------------------------------------------------------------------------------//

	void Graphics::drawPixel(int x, int y, Color_t color)
	{
		if (x >= 0 && x < m_cwindowWidth && y >= 0 && y < m_cwindowHeight)
		{
			m_colorBuffer[y * m_cwindowWidth + x] = color;
		}
	}

	void Graphics::drawLine(int x0, int y0, int x1, int y1, Color_t color)
	{
		ddaLineAlgo(x0, y0, x1, y1, color);
	}

	void Graphics::drawTriangle(eng::Triangle& triangle, Color_t color)
	{
		drawTriangle(
			triangle.points[0].x,
			triangle.points[0].y,
			triangle.points[1].x,
			triangle.points[1].y,
			triangle.points[2].x,
			triangle.points[2].y,
			color);
	}

	void Graphics::drawFilledRectangle(eng::Rectangle& rect, Color_t color)
	{
		for (size_t y = rect.position.y; y < rect.height + rect.position.y; y++)
		{
			for (size_t x = rect.position.x; x < rect.width + rect.position.x; x++)
			{
				drawPixel(x, y, color);
			}
		}
	}

	/*

		0-------1
		|		|
		|		|
		|		|
		3-------2

	*/
	void Graphics::drawRectangle(eng::Rectangle& rect, Color_t color)
	{
		//0---------1
		drawLine(rect.position.x, rect.position.y,
			rect.position.x + rect.width, rect.position.y,
			color);

		//1---------2
		drawLine(rect.position.x + rect.width, rect.position.y,
			rect.position.x + rect.width, rect.position.y + rect.height,
			color);

		//2---------3
		drawLine(rect.position.x + rect.width, rect.position.y + rect.height,
			rect.position.x, rect.position.y + rect.height,
			color);

		//3---------0
		drawLine(rect.position.x, rect.position.y + rect.height,
			rect.position.x, rect.position.y,
			color);

	}

	void Graphics::drawCircle()
	{
	}

	void Graphics::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color_t color)
	{
		drawLine(x0, y0, x1, y1, color);
		drawLine(x1, y1, x2, y2, color);
		drawLine(x2, y2, x0, y0, color);
	}

	void Graphics::drawFilledTriangle(eng::Triangle& trig, Color_t color)
	{

	}

	void Graphics::fillFlatBottomTriangle()
	{
	}

	void Graphics::fillFlatTopTriangle()
	{
	}

	void Graphics::ddaLineAlgo(int x0, int y0, int x1, int y1, Color_t color)
	{
		int deltaX = x1 - x0;
		int deltaY = y1 - y0;

		int sideLength = abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY);

		float incX = deltaX / (float)sideLength;
		float incY = deltaY / (float)sideLength;

		float currentX = x0;
		float currentY = y0;

		for (size_t i = 0; i <= sideLength; i++)
		{
			drawPixel(round(currentX), round(currentY), color);
			currentX += incX;
			currentY += incY;
		}
	}
}