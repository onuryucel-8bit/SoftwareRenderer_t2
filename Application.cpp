#include "Application.h"

namespace eng
{

Application::Application()
{
	initWindow();
	f_running = true;

	gp.init(m_renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Application::~Application()
{
}

void Application::run()
{
	setup();
	
	SDL_Event event;			
	
	while (f_running)
	{		
		input(event);
		update();
		draw();
	}
		
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	
}

void Application::initWindow()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return;
	}
		
	if (m_window = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN); m_window == nullptr)
	{
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return;
	}

	// Create a renderer
	m_renderer = SDL_CreateRenderer(m_window, nullptr);
	if (m_renderer == nullptr)
	{
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return;
	}

}


void Application::input(SDL_Event& event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			f_running = false;
		}

		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == SDLK_ESCAPE)
			{
				f_running = false;
			}
		}
	}
}

void Application::update()
{
}

void Application::draw()
{		
	SDL_RenderClear(m_renderer);
	gp.clearColorBuffer(0x2000'9000);
	
	//XOR
	for (size_t y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (size_t x = 0; x < WINDOW_WIDTH; x++)
		{	
			Color_t color;
			color = (x ^ y);
			color = gp.createColor(color , color, color);

			gp.drawPixel(x, y, color);
		}
	}

	gp.drawColorBuffer();	
}

void Application::setup()
{	
	/*
	rect.position.x = 60;
	rect.position.y = 70;
	rect.width = 30;
	rect.height = 20;
	*/

}

}