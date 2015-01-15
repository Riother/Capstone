#ifndef VOXEL_GROUP_H
#define VOXEL_GROUP_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Qt\qglobal.h>
#include "RenderableInfo.h"

typedef glm::vec3 Vector3;

class VoxelGroup
{
	static const int DIMENSIONS = 5;
	Vector3 Position;
	GeometryInfo* Cube;
	ShaderInfo* Shader;
	RenderableInfo* voxels[DIMENSIONS * DIMENSIONS * DIMENSIONS];
public:
	VoxelGroup(Vector3 position, GeometryInfo* cube, ShaderInfo* shader);

};

#endif