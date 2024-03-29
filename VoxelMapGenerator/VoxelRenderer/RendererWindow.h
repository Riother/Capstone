#ifndef RENDERER_WINDOW_H
#define RENDERER_WINDOW_H

#include <GL\glew.h>
#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <Qt\qdebug.h>
#include <iostream>
#include <fstream>
#include "ParameterType.h"
#include "BufferInfo.h"
#include "GeometryInfo.h"
#include "ShaderInfo.h"
#include "RenderableInfo.h"
#include "Camera.h"
#include "Voxel.h"

using std::string;
using std::istreambuf_iterator;
using std::ifstream;
using std::cout;

typedef glm::mat4 Matrix4;

#define RENDERER RendererWindow::getRenderer()

class RendererWindow : public QGLWidget
{
	Q_OBJECT

	
	static const int MAX_INFOS = 10;
	static const int MAX_RENDERABLES = 1000;
	static const int MAX_CUBES = 1000000;
	static const int MAX_DIMENSION_VALUE = 10;
	Voxel Cubes[MAX_CUBES];
	int cubeCount;
	int mapLength;
	int mapWidth;
	int mapHeight;
	float cameraSpeed;
	bool leftClick;
	
private:
	//Singleton
	RendererWindow(const RendererWindow&);
	RendererWindow& operator=(const RendererWindow&);
	static RendererWindow* rendererInstance;
	//Singleton
public:
	//Singleton
	static RendererWindow& getRenderer();
	//Singleton
	RendererWindow();
	Camera camera;
	bool setVisibility;
	int renderableCount;
	int geometryCount;
	int shaderCount;
	void initializeGL();
	void paintGL();
	Matrix4 perspectiveMatrix;
	QTimer updateTimer;
	BufferInfo buffers[MAX_INFOS];
	GeometryInfo geometryInfos[MAX_INFOS];
	ShaderInfo shaderInfos[MAX_INFOS];
	RenderableInfo renderableInfos[MAX_RENDERABLES];
	GLuint frameBufferID;
	GLuint colorTextureID;
	GLuint depthTextureID;

	GeometryInfo* addGeometry(const void* verts, GLuint vertexDataSize, ushort* indices, uint numIndices, GLuint indexingMode);
	ShaderInfo* createShaderInfo(const char* vertexShaderCode, const char* fragmentShaderCode);
	void compileShader(const char* shaderCode, GLuint shaderID);
	RenderableInfo* addRenderable(GeometryInfo* whatGeometry, const Matrix4& whereMatrix, ShaderInfo* howshaders, bool& isVisible, Vector4 color, int texture, bool useMap = false);
	void addShaderStreamedParameter(GeometryInfo* geometry,	uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride);
	void addRenderableUniformParameter(RenderableInfo* renderable, const char* name, ParameterType parameterType, const float* value);
	int addTexture(const char* fileName);
	int addTexture(QImage image);
	QImage loadImage(const char* fileName);
	void prepareTexture(QImage image, GLuint type);
	void setupFrameBuffer();

	string readShaderCode(const char* fileName);
	Voxel* addCube(Vector4 color, Vector3 position, GLuint textureID, int height, bool isVisible);
	void drawStuff();
	void drawMap();
//Mouse & Keyboard Inputs
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void updateDimensions(int length, int width, int height);
	void updateDimensions(Vector3 newDimensions);
	void updateCameraSpeed(float newSpeed);
	int getMaxRenderables();
	void updateCubes(int index, Voxel cube);
private slots:
		void Update();
};

#endif