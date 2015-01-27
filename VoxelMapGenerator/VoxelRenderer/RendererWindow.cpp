#include "RendererWindow.h"

const int MAX_INFOS = 10;
const int MAX_RENDERABLES = 1000;
const int MAX_DIMENSION_VALUE = 10;
const int MEGABYTE = 1048576;

RendererWindow * RendererWindow::rendererInstance;
RendererWindow& RendererWindow::getRenderer()
{
	if(rendererInstance == NULL)
		rendererInstance = new RendererWindow();
	return *rendererInstance;
}

void RendererWindow::initializeGL()
{
	glewInit();

	cubeCount = 0;
	renderableCount = 0;
	geometryCount = 0;
	shaderCount = 0;
	cameraSpeed = 0.1f;
	perspectiveMatrix = glm::perspective(90.0f, (float)(width())/height(), 0.1f, 1000.0f);

	setVisibility = true;

	for(int i = 0; i < MAX_INFOS; i++)
	{
		buffers[i].remainingSize = MEGABYTE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(Update()));
	updateTimer.start(0);
	//setupFrameBuffer();
	leftClick = false;
	setMouseTracking(false);
}

void RendererWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//drawStuff();
	drawMap();
}

RendererWindow::RendererWindow()
{
}

GeometryInfo* RendererWindow::addGeometry(const void* verts, GLuint vertexDataSize, ushort* indices, uint numIndices, GLuint indexingMode)
{
	int counter = 0;
	while(buffers[counter].remainingSize < vertexDataSize + (numIndices * sizeof(ushort *)))
	{
		counter++;
	}

	if(buffers[counter].remainingSize == MEGABYTE)
	{
		glGenBuffers(1, &buffers[counter].glBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[counter].glBufferID);
		glBufferData(GL_ARRAY_BUFFER, MEGABYTE, 0, GL_STATIC_DRAW);
	}
	
	GLuint offset = (MEGABYTE) - buffers[counter].remainingSize;
	GLuint indexOffset = vertexDataSize + offset;
	unsigned int bufferID = buffers[counter].glBufferID;
	geometryInfos[geometryCount] = GeometryInfo(offset, numIndices, indexOffset, indexingMode, indices, bufferID);
	buffers[counter].remainingSize -= (vertexDataSize + (numIndices * sizeof(ushort)));

	glBindBuffer(GL_ARRAY_BUFFER, buffers[counter].glBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, geometryInfos[geometryCount].offset, vertexDataSize, verts);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[counter].glBufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, geometryInfos[geometryCount].indexOffset, numIndices* sizeof(ushort), indices);
	
	glGenVertexArrays(1, &geometryInfos[geometryCount].vertexArrayID);
	glBindVertexArray(geometryInfos[geometryCount].vertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[counter].glBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[counter].glBufferID);

	return &geometryInfos[geometryCount++];
}

ShaderInfo* RendererWindow::createShaderInfo(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	//string tempShaderCode = readShaderCode(vertexShaderCode);
	//const char* adapter[1];
	//adapter[0] = tempShaderCode.c_str();
	//glShaderSource(vertexShaderID, 1, adapter, 0);
	//tempShaderCode = readShaderCode(fragmentShaderCode);
	//adapter[0] = tempShaderCode.c_str();
	//glShaderSource(fragShaderID, 1, adapter, 0);

	compileShader(vertexShaderCode, vertexShaderID);
	compileShader(fragmentShaderCode, fragShaderID);

	shaderInfos[shaderCount] = ShaderInfo(glCreateProgram());
	glAttachShader(shaderInfos[shaderCount].programID, vertexShaderID);
	glAttachShader(shaderInfos[shaderCount].programID, fragShaderID);

	glLinkProgram(shaderInfos[shaderCount].programID);

	return &shaderInfos[shaderCount++];
}

void RendererWindow::compileShader(const char* shaderCode, GLuint shaderID)
{
	string tempShaderCode = readShaderCode(shaderCode);
	const char* adapter[1];
	adapter[0] = tempShaderCode.c_str();
	glShaderSource(shaderID, 1, adapter, 0);

	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* buffer = new char[logLength];
		GLsizei happyGL;
		glGetShaderInfoLog(shaderID, logLength, &happyGL, buffer);
		qDebug() << buffer;
		delete[] buffer;
	}
}

RenderableInfo* RendererWindow::addRenderable(GeometryInfo* whatGeometry, const Matrix4& whereMatrix, ShaderInfo* howShaders, bool& isVisible, Vector4 color, int texture, bool useMap)
{
	renderableInfos[renderableCount] = RenderableInfo(whatGeometry, whereMatrix, howShaders, isVisible, texture, color, useMap);
	return &renderableInfos[renderableCount++];
}

void RendererWindow::addShaderStreamedParameter(GeometryInfo* geometry, uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride)
{
	glBindVertexArray(geometry->vertexArrayID);
	glEnableVertexAttribArray(layoutLocation);

	glVertexAttribPointer(layoutLocation, parameterType/ sizeof(float), GL_FLOAT, GL_FALSE, bufferStride, (void*)(geometry->offset + bufferOffset));
}

void RendererWindow::addRenderableUniformParameter(RenderableInfo* renderable, const char* name, ParameterType parameterType, const float* value)
{
	glUseProgram(renderable->howShaders->programID);
	GLuint location = glGetUniformLocation(renderable->howShaders->programID, name);

	switch(parameterType)
	{
	case ParameterType::PT_FLOAT:
		{
			glUniform1f(location, *value);
		}
	case ParameterType::PT_VECTOR2:
		{
			glUniform2fv(location, 1, value);
		}
	case ParameterType::PT_VECTOR3:
		{
			glUniform3fv(location, 1, value);
		}
	case ParameterType::PT_VECTOR4:
		{
			glUniform4fv(location, 1, value);
		}
	case ParameterType::PT_MATRIX3:
		{
			glUniformMatrix3fv(location, 1, GL_FALSE, value);
		}
	case ParameterType::PT_MATRIX4:
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, value);
		}
	}
}

int RendererWindow::addTexture(const char* fileName)
{
	QImage image;

	image.load(fileName);

	if(!image.load(fileName))
	{
		std::cerr<<"Could not load image "<<fileName<<".";
		return -1;
	}

	image = QGLWidget::convertToGLFormat(image);
	int w = image.width();
	int h = image.height();
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

	return textureID;
}

int RendererWindow::addTexture(QImage image)
{
	image = QGLWidget::convertToGLFormat(image);
	int w = image.width();
	int h = image.height();

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

	return textureID;
}

QImage RendererWindow::loadImage(const char* fileName)
{
	QImage image;
	image.load(fileName);

	if(!image.load(fileName))
	{
		std::cerr<<"Could not load image"<<fileName<<".";
	}

	return image;
}

void RendererWindow::prepareTexture(QImage image, GLuint type)
{
	image = QGLWidget::convertToGLFormat(image);
	int w = image.width();
	int h = image.height();

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(type, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
}

void RendererWindow::setupFrameBuffer()
{
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferID);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &colorTextureID);
	glBindTexture(GL_TEXTURE_2D, colorTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 255, 255, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureID, 0);
	glGenTextures(1, &depthTextureID);
	glBindTexture(GL_TEXTURE_2D, depthTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 255, 255, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureID, 0);

	GLuint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
		qDebug()<<"Frame buffer not complete...";
}

string RendererWindow::readShaderCode(const char* fileName)
{
	ifstream input(fileName);
	if(! input.good())
	{
		cout<<"File failed to load: "<<fileName;
		exit(1);
	}
	return string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());
}

void RendererWindow::drawStuff()
{
	for(int i = 0; i < renderableCount; i++)
	{
		if(renderableInfos[i].isVisible)
		{
			glUseProgram(renderableInfos[i].howShaders->programID);


			addRenderableUniformParameter(&renderableInfos[i], "transformation", ParameterType::PT_MATRIX4, &(perspectiveMatrix * camera.getWorldToViewMatrix() * renderableInfos[i].whereMatrix)[0][0]);
			addRenderableUniformParameter(&renderableInfos[i], "cameraPosition", ParameterType::PT_VECTOR3, &camera.getPosition()[0]);

			//addRenderableUniformParameter(&renderableInfos[i], "pureTrans", ParameterType::PT_MATRIX4, &(renderableInfos[i].whereMatrix)[0][0]);
			//addRenderableUniformParameter(&renderableInfos[i], "lightPosition", ParameterType::PT_VECTOR3, &lightPosition[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "lightColor", ParameterType::PT_VECTOR3, &lightPosition[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "specularLight", ParameterType::PT_VECTOR3, &specularLight[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "diffuseLight", ParameterType::PT_VECTOR3, &diffuseLight[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "ambientLight", ParameterType::PT_VECTOR3, &ambientLight[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "specularExponent", ParameterType::PT_FLOAT, &specularExponent);
			addRenderableUniformParameter(&renderableInfos[i], "color", ParameterType::PT_VECTOR3, &renderableInfos[i].color[0]);
			//addRenderableUniformParameter(&renderableInfos[i], "modelToWorld", ParameterType::PT_MATRIX4, &renderableInfos[i].whereMatrix[0][0]);
			//addRenderableUniformParameter(&renderableInfos[i], "octave", ParameterType::PT_FLOAT, &octave);
			//addRenderableUniformParameter(&renderableInfos[i], "meltingRange", ParameterType::PT_FLOAT, &meltingRange);

			if(renderableInfos[i].textureID == -1)
			{
				//dont use image
				float useImage = 0;
				addRenderableUniformParameter(&renderableInfos[i], "useImage", ParameterType::PT_FLOAT, &useImage);
			}
			else
			{
				//use image
				float useImage = 1;
				addRenderableUniformParameter(&renderableInfos[i], "useImage", ParameterType::PT_FLOAT, &useImage);

				glActiveTexture(renderableInfos[i].textureID);
			}

			//if(renderableInfos[i].useMap)
			//	glBindTexture(GL_TEXTURE_CUBE_MAP, renderableInfos[i].textureID);
			//else
			//	glBindTexture(GL_TEXTURE_2D, renderableInfos[i].textureID);

			glBindVertexArray(renderableInfos[i].whatGeometry->vertexArrayID);

			glDrawElements(renderableInfos[i].whatGeometry->indexingMode, renderableInfos[i].whatGeometry->numIndices, GL_UNSIGNED_SHORT, (void*)(renderableInfos[i].whatGeometry->indexOffset));
		}
	}
}

void RendererWindow::drawMap()
{
	int cubeLocation = 0;
	glUseProgram(renderableInfos[cubeLocation].howShaders->programID);
	for(int i = 0; i < cubeCount; i++)
	{
		for(int j = 0; j < Cubes[i].Height; j++)
		{
			if(Cubes[i].IsVisible)
			{
				Matrix4 whereMatrix = glm::translate(Cubes[i].Position + Vector3(0, j, 0)) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
				addRenderableUniformParameter(&renderableInfos[cubeLocation], "transformation", ParameterType::PT_MATRIX4, &(perspectiveMatrix * camera.getWorldToViewMatrix() * whereMatrix)[0][0]);
				addRenderableUniformParameter(&renderableInfos[cubeLocation], "cameraPosition", ParameterType::PT_VECTOR3, &camera.getPosition()[0]);
				addRenderableUniformParameter(&renderableInfos[cubeLocation], "color", ParameterType::PT_VECTOR3, &Cubes[i].Color[0]);

				if(Cubes[i].TextureID == -1)
				{
					//dont use image
					float useImage = 0;
					addRenderableUniformParameter(&renderableInfos[cubeLocation], "useImage", ParameterType::PT_FLOAT, &useImage);
				}
				else
				{
					//use image
					float useImage = 1;
					addRenderableUniformParameter(&renderableInfos[cubeLocation], "useImage", ParameterType::PT_FLOAT, &useImage);

					glActiveTexture(Cubes[i].TextureID);
				}

				glBindTexture(GL_TEXTURE_2D, Cubes[i].TextureID);

				glBindVertexArray(renderableInfos[cubeLocation].whatGeometry->vertexArrayID);

				glDrawElements(renderableInfos[cubeLocation].whatGeometry->indexingMode, renderableInfos[cubeLocation].whatGeometry->numIndices, GL_UNSIGNED_SHORT, (void*)(renderableInfos[cubeLocation].whatGeometry->indexOffset));
			}
		}
	}
	//for(int x = 0; x < mapWidth; x++)
	//{
	//	for(int y = 0; y < mapHeight; y++)
	//	{
	//		for(int z = 0; z < mapLength; z++)
	//		{
	//			if(Cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].IsVisible)
	//			{
	//				Matrix4 whereMatrix = glm::translate(Vector3(x, -y, -z)) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	//				addRenderableUniformParameter(&renderableInfos[cubeLocation], "transformation", ParameterType::PT_MATRIX4, &(perspectiveMatrix * camera.getWorldToViewMatrix() * whereMatrix)[0][0]);
	//				addRenderableUniformParameter(&renderableInfos[cubeLocation], "cameraPosition", ParameterType::PT_VECTOR3, &camera.getPosition()[0]);
	//				addRenderableUniformParameter(&renderableInfos[cubeLocation], "color", ParameterType::PT_VECTOR3, &Cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].Color[0]);

	//				if(Cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID == -1)
	//				{
	//					//dont use image
	//					float useImage = 0;
	//					addRenderableUniformParameter(&renderableInfos[cubeLocation], "useImage", ParameterType::PT_FLOAT, &useImage);
	//				}
	//				else
	//				{
	//					//use image
	//					float useImage = 1;
	//					addRenderableUniformParameter(&renderableInfos[cubeLocation], "useImage", ParameterType::PT_FLOAT, &useImage);

	//					glActiveTexture(Cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID);
	//				}

	//				glBindTexture(GL_TEXTURE_2D, Cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID);

	//				glBindVertexArray(renderableInfos[cubeLocation].whatGeometry->vertexArrayID);

	//				glDrawElements(renderableInfos[cubeLocation].whatGeometry->indexingMode, renderableInfos[cubeLocation].whatGeometry->numIndices, GL_UNSIGNED_SHORT, (void*)(renderableInfos[cubeLocation].whatGeometry->indexOffset));
	//			}
	//		}
	//	}
	//}
}

Voxel* RendererWindow::addCube(Vector4 color, Vector3 position, GLuint textureID, int height, bool isVisible)
{
	Cubes[cubeCount] = Voxel(color, position, textureID, height, isVisible);
	return &Cubes[cubeCount++];
}

void RendererWindow::Update()
{
	if(leftClick)
		camera.update();
	camera.updateCameraSpeed(cameraSpeed);
	repaint();
}

void RendererWindow::mouseMoveEvent(QMouseEvent* e)
{
	camera.mouseUpdate(Vector2(e->x(), e->y()));
	repaint();
}

void RendererWindow::mousePressEvent(QMouseEvent* e)
{
	if(e->button() == Qt::LeftButton)
	{
		leftClick = true;
	}
}

void RendererWindow::mouseReleaseEvent(QMouseEvent* e)
{
	if(e->button() == Qt::LeftButton)
	{
		leftClick = false;
	}
}

void RendererWindow::updateDimensions(int length, int width, int height)
{
	mapLength = length;
	mapWidth = width;
	mapHeight = height;
}

void RendererWindow::updateDimensions(Vector3 newDimensions)
{
	mapLength = newDimensions.z;
	mapWidth = newDimensions.x;
	mapHeight = newDimensions.y;
}

void RendererWindow::updateCameraSpeed(float newSpeed)
{
	cameraSpeed = newSpeed;
}

int RendererWindow::getMaxRenderables()
{
	return MAX_RENDERABLES;
}

void RendererWindow::updateCubes(int index, Voxel cube)
{
	Cubes[index] = cube;
}