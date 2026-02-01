#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../libsLocal/glm/glm.hpp"

namespace eng
{
	class ObjReader
	{
	public:
		ObjReader();
		~ObjReader();

		//TODO use filesystem
		std::vector<glm::vec3> read(std::string path);

	private:

	};
}