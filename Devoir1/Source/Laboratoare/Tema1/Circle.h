#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill = false);


}

