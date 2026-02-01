#include "ObjReader.h"

namespace eng
{

    ObjReader::ObjReader()
    {
    }

    ObjReader::~ObjReader()
    {
    }

    std::vector<glm::vec3> ObjReader::read(std::string path)
    {
        std::vector<glm::vec3> vertexList;

        std::ifstream file(path);

        std::string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (line.starts_with("v "))
                {
                    std::istringstream iss(line);

                    char v;
                    glm::vec3 vertex;

                    iss >> v >> vertex.x >> vertex.y >> vertex.z;

                    vertexList.push_back(vertex);
                }
                
            }
        }
        else
        {
            std::cout << "Unable to open file!\n";
        }

        return vertexList;
    }
}