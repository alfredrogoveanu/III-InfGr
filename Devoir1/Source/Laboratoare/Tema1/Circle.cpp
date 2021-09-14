/*#include "Circle.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	
	glBegin(GL.GL_LINE_LOOP);
	for (int i = 0; i <= 8; i++) {
		double angle = 2 * Math.PI * i / 8;
		double x = Math.cos(angle);
		double y = Math.sin(angle);
		gl.glVertex2d(glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);

	glEnd();

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}*/