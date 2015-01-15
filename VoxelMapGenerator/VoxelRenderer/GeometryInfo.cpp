#include "GeometryInfo.h"

GeometryInfo::GeometryInfo()
{
	isAvailable = true;
}

GeometryInfo::GeometryInfo(GLuint offset, uint numIndices, GLuint indexOffset, GLuint indexingMode, ushort* indices, unsigned int bufferID)
{
	this->offset = offset;
	this->numIndices = numIndices;
	this->indexOffset = indexOffset;
	this->indexingMode = indexingMode;
	this->indices = indices;
	this->bufferID = bufferID;
	isAvailable = true;
}