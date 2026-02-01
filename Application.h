#pragma once

#include <cstdint>
#include <iostream>
#include <chrono>
#include <vector>

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
		glm::vec2 perspectiveProject(glm::vec3& vec);

		void initWindow();
		void update(float dt);
		void input(SDL_Event& event);
		void draw();
		void setup();

		float test_varx = 0.0f;
		float test_vary = 0.0f;
		float t = 0.0f;
		Color_t test_color;
		float FOV = 640;

		glm::vec3 m_camera;

		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec2> m_projectedVertexs;

		eng::Graphics gp;

		bool f_running;

		eng::RenderContext m_context;
	};

}