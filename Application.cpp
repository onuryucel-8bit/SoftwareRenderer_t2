#include "Application.h"

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
	gp.clearColorBuffer(0x2000'6000);
	
	//gp.drawGrid(16, 16, Color::Blue);
	//gp.drawDots(0, 0, Color::Blue);

	//gp.drawLine(0, 0, 180, 180, Color::Red);
	//gp.drawTriangle(100, 10, 50, 150, 150, 150, Color::Red);	
	gp.drawRectangle(rect, Color::Red);
	gp.drawColorBuffer();
	// Present the rendered frame
	
}

void Application::setup()
{	
	rect.points[0].x = 10;
	rect.points[0].y = 10;
	rect.points[1].x = 100;
	rect.points[1].y = 10;
	rect.points[2].x = 100;
	rect.points[2].y = 100;
	rect.points[3].x = 10;
	rect.points[3].y = 100;
}
