#include "Application.h"

namespace eng
{

Application::Application()	
{	
	initWindow();
	f_running = true;

	gp.init(m_context);
}

Application::~Application()
{
}

void Application::run()
{
	setup();
	
	SDL_Event event;			
	
	using Clock = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	TimePoint startTime = Clock::now();
	TimePoint lastTime = startTime;

	while (f_running)
	{

		TimePoint currentTime = Clock::now();		
		float delta = Duration(currentTime - lastTime).count();
		lastTime = currentTime;



		std::string title = std::to_string(1.0f / delta);
		SDL_SetWindowTitle(m_context.window, title.c_str());

		

		input(event);
		update(delta);
		draw();
	}
		
	SDL_DestroyWindow(m_context.window);
	SDL_DestroyRenderer(m_context.renderer);
	SDL_Quit();
	
}

void Application::initWindow()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return;
	}
		
	if (m_context.window = SDL_CreateWindow("Software Renderer", m_context.WindowWidth, m_context.WindowHeight, NULL); m_context.window == nullptr)
	{
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return;
	}

	// Create a renderer
	m_context.renderer = SDL_CreateRenderer(m_context.window, nullptr);
	if (m_context.renderer == nullptr)
	{
		SDL_Log("Renderer could not be created! SDL error: %s\n", SDL_GetError());
		SDL_DestroyWindow(m_context.window);
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

void Application::update(float dt)
{
}

void Application::draw()
{		
	SDL_RenderClear(m_context.renderer);
	gp.clearColorBuffer(0x2000'9000);
	
	//XOR
	for (size_t y = 0; y < m_context.WindowHeight; y++)
	{
		for (size_t x = 0; x < m_context.WindowWidth; x++)
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