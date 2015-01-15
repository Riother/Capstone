#ifndef SHADER_INFO_H
#define SHADER_INFO_H

#include <GL\glew.h>
#include <Qt\qglobal.h>

struct ShaderInfo
{
	ShaderInfo();
	ShaderInfo(GLuint programID);
	GLuint programID;
	bool isAvailable;
};

#endif