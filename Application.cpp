#include "Application.h"

namespace eng
{

Application::Application()	
{	
	initWindow();
	f_running = true;

	gp.init(m_context);

	m_camera.x = 0;
	m_camera.y = 0.0f;
	m_camera.z = -7.0f;
}

Application::~Application()
{
}

glm::vec2 Application::perspectiveProject(glm::vec3& vec)
{
	return glm::vec2((FOV * vec.x) / vec.z, (FOV * vec.y) / vec.z);
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

void Application::transform(glm::vec4 transformedVertices_ret, glm::mat4x4 worldMatrix)
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
	t += 0.07f * dt;

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		glm::vec3 point = m_vertices[i];

		//move the camera
		point.z -= m_camera.z;

		//TODO coordinate system of teapot is weird..
		//point.x *= -1;
		
		//Rotate the teapot
		point.y *= -1;

		//project points on 2d screen
		glm::vec2 projectedPoint = perspectiveProject(point);

		//move projectedPoint to center
		projectedPoint.x += m_context.WindowWidth * 0.5;
		projectedPoint.y += m_context.WindowHeight * 0.5;

		//std::cout << "posx:" << projectedPoint.x << "\n";

		//insert in list
		m_projectedVertexs.push_back(projectedPoint);
	}

}

void Application::draw()
{		
	SDL_RenderClear(m_context.renderer);

	gp.clearColorBuffer(0xff00'0f00);

	//draw vertexs
	for (auto const& point : m_projectedVertexs)
	{
		gp.drawFilledRectangle((int)point.x, (int)point.y, 4, 4, Color::Blue);
	}
		
	gp.drawColorBuffer();

	//TODO 
	m_projectedVertexs.clear();

}

void Application::setup()
{	
	test_varx = m_context.WindowWidth / 2 + 10;
	test_vary = m_context.WindowHeight / 2 + 10;
	t = 0.0f;
	test_color = 0xff00'0000;

	
	//little "cubes"
	/*for (float x = -1; x <= 1; x += 0.25f)
	{
		for (float y = -1; y <= 1; y += 0.25f)
		{
			for (float z = -1; z <= 1; z += 0.25f)
			{
				m_vertices.push_back({ x, y, z});
			}
		}
	}*/

	/*			
		   *--------------*		                 
		  /				 /|
		 /				/ |
		*--------------*  |
		|			   |  |
		|			   |  |
		|			   |  |
		|			   |  *
		|			   | / 
		|			   |/
		*--------------*			
	*/


	/*m_vertices.push_back({ -1,  1,  1 });
	m_vertices.push_back({ -1, -1,  1 });
	m_vertices.push_back({  1, -1,  1 });
	m_vertices.push_back({  1,  1,  1 });
	m_vertices.push_back({ -1,  1,  3 });
	m_vertices.push_back({ -1, -1,  3 });
	m_vertices.push_back({ 1, -1,  3 });
	m_vertices.push_back({ 1, 1,  3 });*/

    //m_vertices = objReader.read("assets/ch.obj");
	m_vertices = objReader.read("assets/holyTEAPOT.obj");

}

}