#include "MapEditorWindow.h"

MapEditorWindow::MapEditorWindow()
{
	mainLayout = new QHBoxLayout;
	mainWidget = new QWidget;

	tabWidget = new QTabWidget;
	tabsLayout = new QVBoxLayout;

	rendererLayout = new QVBoxLayout;

	mapDimensions = new MapDimensionsWidget;

	tabWidget->addTab(mapDimensions, "Map Dimensions");
	tabsLayout->addWidget(tabWidget);
	mainLayout->addLayout(tabsLayout);
	mainLayout->addLayout(rendererLayout);

	rendererLayout->addWidget(&RENDERER);
	RENDERER.setMinimumSize(700, 600);
	mainWidget->setLayout(mainLayout);

	setCentralWidget(mainWidget);
	show();

	//RENDERER.show();

	isVisible = true;
	createMap();

	connect(mapDimensions, SIGNAL(valueChanged()), this, SLOT(updateLoop()));
	//connect(&timer, SIGNAL(timeout()), this, SLOT(updateLoop()));
	timer.start(0);
}

void MapEditorWindow::updateLoop()
{
	int width = mapDimensions->getDimensions().x;
	int height = mapDimensions->getDimensions().y;
	int length = mapDimensions->getDimensions().z;
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			for(int z = 0; z < length; z++)
			{
				cubeRenderables[x * height * length + y * length + z]->isVisible = (rand() % 2 == 0) ? true : false;
			}
		}
	}
	RENDERER.updateDimensions(mapDimensions->getDimensions());
	RENDERER.updateCameraSpeed((float)mapDimensions->getCameraSpeed() / 100);
	qDebug()<<"Updating";
}

void MapEditorWindow::createMap()
{
	cubeInfo = RENDERER.addGeometry(cube.vertices, cube.SIZE * (3 * sizeof(float)), cube.indices, cube.AMOUNT_OF_VERTICES, GL_TRIANGLES);

	RENDERER.addShaderStreamedParameter(cubeInfo, 0, ParameterType::PT_VECTOR3, 0, 6 * sizeof(float));
	RENDERER.addShaderStreamedParameter(cubeInfo, 1, ParameterType::PT_VECTOR3, 3 * sizeof(float), 6 * sizeof(float));

	shaderInfo = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");

	int width = mapDimensions->getDimensions().x;
	int height = mapDimensions->getDimensions().y;
	int length = mapDimensions->getDimensions().z;

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			for(int z = 0; z < length; z++)
			{
				Matrix4 position = glm::translate(Vector3(x, y, z)) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
				cubeRenderables[x * height * length + y * length + z] = RENDERER.addRenderable(cubeInfo, position, shaderInfo, isVisible, Vector4((float)(x / 10), (float)(y / 10), (float)(z / 10), 1.0f), -1, false);
			}
		}
	}

	//RENDERER.addRenderable(cubeInfo, Matrix4(), shaderInfo, isVisible, Vector4(1, 0, 1, 1), -1, false);
	
	//Vector3 position(0, 0, 0);

	//voxels = new VoxelGroup(position, cubeInfo, shaderInfo);

	RENDERER.updateDimensions(mapDimensions->getDimensions());
}

//void MapEditorWindow::createMap()
//{	
//	Neumont::ShapeData cube = Neumont::ShapeGenerator::makeCube();
//	Neumont::ShapeData arrow = Neumont::ShapeGenerator::makeArrow();
//	Neumont::ShapeData sphere = Neumont::ShapeGenerator::makeSphere(20);
//
//	GeometryInfo* cubeInfo   = RENDERER.addGeometry(cube.verts, cube.vertexBufferSize(), cube.indices, cube.numIndices, GL_TRIANGLES);
//	GeometryInfo* sphereInfo = RENDERER.addGeometry(sphere.verts, sphere.vertexBufferSize(), sphere.indices, sphere.numIndices, GL_TRIANGLES);
//	GeometryInfo* arrowInfo  = RENDERER.addGeometry(arrow.verts, arrow.vertexBufferSize(), arrow.indices, arrow.numIndices, GL_TRIANGLES);
//
//	//cube
//	RENDERER.addShaderStreamedParameter(cubeInfo, 0, ParameterType::PT_VECTOR3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(cubeInfo, 1, ParameterType::PT_VECTOR4, Neumont::Vertex::COLOR_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(cubeInfo, 2, ParameterType::PT_VECTOR3, Neumont::Vertex::NORMAL_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(cubeInfo, 3, ParameterType::PT_VECTOR2, Neumont::Vertex::UV_OFFSET, Neumont::Vertex::STRIDE);
//
//	//sphere
//	RENDERER.addShaderStreamedParameter(sphereInfo, 0, ParameterType::PT_VECTOR3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(sphereInfo, 1, ParameterType::PT_VECTOR4, Neumont::Vertex::COLOR_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(sphereInfo, 2, ParameterType::PT_VECTOR3, Neumont::Vertex::NORMAL_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(sphereInfo, 3, ParameterType::PT_VECTOR2, Neumont::Vertex::UV_OFFSET, Neumont::Vertex::STRIDE);
//
//	//arrow
//	RENDERER.addShaderStreamedParameter(arrowInfo, 0, ParameterType::PT_VECTOR3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(arrowInfo, 1, ParameterType::PT_VECTOR4, Neumont::Vertex::COLOR_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(arrowInfo, 2, ParameterType::PT_VECTOR3, Neumont::Vertex::NORMAL_OFFSET, Neumont::Vertex::STRIDE);
//	RENDERER.addShaderStreamedParameter(arrowInfo, 3, ParameterType::PT_VECTOR2, Neumont::Vertex::UV_OFFSET, Neumont::Vertex::STRIDE);
//
//	//cubes
//	ShaderInfo* shaderInfo = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
//	glm::mat4 mat = glm::translate(glm::vec3(2.0f, 0.0f, 3.0f)) * glm::scale(glm::vec3(0.5, 0.5, 0.5));
//	RENDERER.addRenderable(cubeInfo, mat, shaderInfo, isVisible, Vector4(0, 1, 0, 1), -1, false);
//
//	mat = glm::translate(glm::vec3(-2.0f, 0.0f, 3.0f)) * glm::scale(glm::vec3(0.5, 0.5, 0.5));
//	RENDERER.addRenderable(cubeInfo, mat, shaderInfo, isVisible, Vector4(0, 1, 0, 1), -1, false);
//
//	mat = glm::translate(glm::vec3(2.0f, 2.0f, 3.0f)) * glm::scale(glm::vec3(0.5, 0.5, 0.5));
//	RENDERER.addRenderable(arrowInfo, mat, shaderInfo, isVisible, Vector4(0, 1, 0, 1), -1, false);
//
//	mat = glm::translate(glm::vec3(-2.0f, 2.0f, 3.0f)) * glm::scale(glm::vec3(0.5, 0.5, 0.5));
//	RENDERER.addRenderable(arrowInfo, mat, shaderInfo, isVisible, Vector4(0, 1, 0, 1), -1, false);
//
//	//spheres
//	mat = glm::translate(glm::vec3(0.0f, 5.0f, 3.0f)) * glm::scale(glm::vec3(0.3, 0.3, 0.3));
//	RENDERER.addRenderable(sphereInfo, mat, shaderInfo, isVisible, Vector4(0, 1, 0, 1), -1, false);
//}