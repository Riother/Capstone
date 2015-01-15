#ifndef CUBE_H
#define CUBE_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Qt\qglobal.h>

typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;

struct Cube
{
	static const uint SIZE = 138;
	static const uint AMOUNT_OF_VERTICES = 36;

	Vector3 vertices[SIZE];
	ushort indices[AMOUNT_OF_VERTICES];
	Cube();
	void createCubeVerticesAndColor();
	void createCubeIndices();
};

#endif