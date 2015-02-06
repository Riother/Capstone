#ifndef VOXEL_H
#define VOXEL_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Qt\qlist.h>

typedef glm::vec4 Vector4;
typedef glm::vec3 Vector3;

struct Voxel
{
	static const int MAX_HEIGHT = 100;
	QList<Vector4> Color;
	Vector3 Position;
	QList<GLuint> TextureID;
	int Height;
	QList<bool> IsVisible;
	Voxel(Vector4 color, Vector3 position, GLuint textureID, int height, bool isVisible);
	Voxel();
};

#endif