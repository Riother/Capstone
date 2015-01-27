#ifndef GEOMETRY_INFO_H
#define GEOMETRY_INFO_H

#include <GL\glew.h>
#include <Qt\qglobal.h>

struct GeometryInfo
{
	GLuint indexingMode;
	GLuint offset;
	GLuint indexOffset;
	uint numIndices;
	unsigned int vertexArrayID;
	unsigned int bufferID;
	ushort* indices;
	bool isAvailable;
	GeometryInfo();
	GeometryInfo(GLuint offset, uint numIndices, GLuint indexOffset, GLuint indexingMode, ushort* indices, unsigned int bufferID);
};

#endif