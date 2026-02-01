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

void Application::initWindow()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return;
	}

	if (m_context.window = SDL_CreateWindow("Software Renderer", m_context.WindowWidth, m_context.WindowHeight, SDL_WINDOW_FULLSCREEN); m_context.window == nullptr)
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

void Application::run()
{
	setup();
	
	SDL_Event event;			
	
	using Clock = std::chrono::steady_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	TimePoint startTime = Clock::now();
	TimePoint lastTime = startTime;

	test_varx = m_context.WindowWidth / 2;
	test_vary = m_context.WindowHeight / 2;

	while (f_running)
	{

		TimePoint currentTime = Clock::now();		
		float delta = Duration(currentTime - lastTime).count();
		lastTime = currentTime;

		std::string fps = std::to_string(1.0f / delta);
		SDL_SetWindowTitle(m_context.window, fps.c_str());

		input(event);
		update(delta);
		draw();
	}
		
	SDL_DestroyWindow(m_context.window);
	SDL_DestroyRenderer(m_context.renderer);
	SDL_Quit();
	
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
	float cx = m_context.WindowWidth * 0.5f;
	float cy = m_context.WindowHeight * 0.5f;

	float r = 100.0f;

	test_varx = cx + cos(t) * r;
	test_vary = cy + sin(t) * r;

	t += dt * 5;

	test_color += 0x0000'0005;

	
}

void Application::draw()
{		
	SDL_RenderClear(m_context.renderer);
	gp.clearColorBuffer(0xff00'0f00);
	
	//gp.drawLine(m_context.WindowWidth / 2, m_context.WindowHeight / 2, test_varx, test_vary, test_color);

	gp.drawFilledRectangle(10, 10, 60, 32, Color::Blue);

	gp.drawColorBuffer();	
}

void Application::setup()
{	
	test_varx = m_context.WindowWidth / 2 + 10;
	test_vary = m_context.WindowHeight / 2 + 10;
	t = 0.0f;
	test_color = 0xff00'0000;
}

}