#ifndef VOXEL_H
#define VOXEL_H

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef glm::vec4 Vector4;
typedef glm::vec3 Vector3;

struct Voxel
{
	Vector4 Color;
	Vector3 Position;
	GLuint TextureID;
	int Height;
	bool IsVisible;
	Voxel(Vector4 color, Vector3 position, GLuint textureID, int height, bool isVisible);
	Voxel();
};

#endif