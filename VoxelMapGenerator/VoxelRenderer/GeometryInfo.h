#ifndef GEOMETRY_INFO_H
#define GEOMETRY_INFO_H

#include <GL\glew.h>
#include <Qt\qglobal.h>

struct GeometryInfo
{
	GeometryInfo();
	GeometryInfo(GLuint offset, uint numIndices, GLuint indexOffset, GLuint indexingMode, ushort* indices, unsigned int bufferID);
	unsigned int vertexArrayID;
	unsigned int bufferID;
	ushort* indices;
	uint numIndices;
	GLuint indexingMode;
	GLuint offset;
	GLuint indexOffset;
	bool isAvailable;
};

#endif