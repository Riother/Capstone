#include "MapEditorWindow.h"

MapEditorWindow::MapEditorWindow()
{
	mainLayout = new QHBoxLayout;
	mainWidget = new QWidget;

	tabWidget = new QTabWidget;
	tabsLayout = new QVBoxLayout;

	rendererLayout = new QVBoxLayout;

	mapDimensions = new MapDimensionsWidget;
	editorWidget = new EditorWidget(mapDimensions->getDimensions());

	tabWidget->addTab(mapDimensions, "Map Dimensions");
	tabWidget->addTab(editorWidget, "Map Editor");
	tabsLayout->addWidget(tabWidget);
	mainLayout->addLayout(tabsLayout);
	mainLayout->addLayout(rendererLayout);

	rendererLayout->addWidget(&RENDERER);
	RENDERER.setMinimumSize(700, 600);
	mainWidget->setLayout(mainLayout);

	QMenu* fileMenu = menuBar()->addMenu("File");

	QAction* action;
	fileMenu->addAction(action = new QAction("Load Map", this));
	action->setShortcut(QKeySequence::Open);
	connect(action, SIGNAL(triggered()), this, SLOT(loadMap()));

	fileMenu->addAction(action = new QAction("Load Map From Image", this));
	action->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
	connect(action, SIGNAL(triggered()), this, SLOT(loadMapFromImage()));

	fileMenu->addAction(action = new QAction("Save Map", this));
	action->setShortcut(QKeySequence::Save);
	connect(action, SIGNAL(triggered()), this, SLOT(saveMap()));

	fileMenu->addAction(action = new QAction("Save Map As...", this));
	action->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
	connect(action, SIGNAL(triggered()), this, SLOT(saveMapAs()));

	setCentralWidget(mainWidget);
	show();

	//RENDERER.show();
	prepareAssets();

	connect(mapDimensions, SIGNAL(valueChanged()), this, SLOT(updateLoop()));
	connect(editorWidget, SIGNAL(valueChanged()), this, SLOT(updateLoop()));
	connect(editorWidget, SIGNAL(currentIndexChanged()), this, SLOT(updateLoop()));
	connect(editorWidget, SIGNAL(heightChanged()), this, SLOT(updateHeight()));
	//connect(&timer, SIGNAL(timeout()), this, SLOT(updateLoop()));
	updateLoop();
}

void MapEditorWindow::updateLoop()
{
	int width = mapDimensions->getDimensions().x;
	int length = mapDimensions->getDimensions().z;

	int chosenX = editorWidget->getPosition().x;
	int chosenY = editorWidget->getPosition().y;
	editorWidget->setHeight(cubes[chosenX * width + chosenY].Height);



	//for(int x = 0; x < MAX_DIMENSION_VALUE; x++)
	//{
	//	for(int y = 0; y < MAX_DIMENSION_VALUE; y++)
	//	{
	//		for(int z = 0; z < cubes[x * width + y].Height; z++)
	//		{
	//			if(x == chosenX && z == chosenZ && y >= chosenHeight)
	//			{
	//				//cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].IsVisible = false;
	//				//cubeRenderables[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z]->isVisible = false;
	//			}
	//			else if(x == chosenX && z == chosenZ && y < chosenHeight)
	//			{
	//				//cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].IsVisible = true;
	//				//cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID = editorWidget->getTexture();
	//				//cubeRenderables[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z]->isVisible = true;
	//			}
	//		}
	//	}
	//}

	editorWidget->updateRanges(mapDimensions->getDimensions());
	//RENDERER.updateDimensions(mapDimensions->getDimensions());
	RENDERER.updateCameraSpeed((float)mapDimensions->getCameraSpeed() / 100);
	//RENDERER.updateCubes(cubes);
}

void MapEditorWindow::updateHeight()
{
	int width = mapDimensions->getDimensions().x;
	int length = mapDimensions->getDimensions().z;

	int chosenX = editorWidget->getPosition().x;
	int chosenY = editorWidget->getPosition().y;
	int index = chosenX * width + chosenY;
	cubes[index].Height = editorWidget->getChosenHeight();
	RENDERER.updateCubes(index, cubes[index]);
}

void MapEditorWindow::prepareAssets()
{
	//Cube
	cubeInfo = RENDERER.addGeometry(cube.vertices, cube.SIZE * (3 * sizeof(float)), cube.indices, cube.AMOUNT_OF_VERTICES, GL_TRIANGLES);

	RENDERER.addShaderStreamedParameter(cubeInfo, 0, ParameterType::PT_VECTOR3, 0, 12 * sizeof(float));
	RENDERER.addShaderStreamedParameter(cubeInfo, 1, ParameterType::PT_VECTOR3, 3 * sizeof(float), 12 * sizeof(float));
	RENDERER.addShaderStreamedParameter(cubeInfo, 2, ParameterType::PT_VECTOR3, 6 * sizeof(float), 12 * sizeof(float));
	RENDERER.addShaderStreamedParameter(cubeInfo, 3, ParameterType::PT_VECTOR3, 9 * sizeof(float), 12 * sizeof(float));

	shaderInfo = RENDERER.createShaderInfo("SimpleVertexShaderCode.glsl", "SimpleFragmentShaderCode.glsl");
	Matrix4 position = glm::translate(Vector3(0, 0, 0)) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	RENDERER.addRenderable(cubeInfo, position, shaderInfo, isVisible, Vector4(0, 0, 0, 1.0f), -1, false);
	
	//Textures
	textures[0] = RENDERER.addTexture("Grass.png");
	textures[1] = RENDERER.addTexture("Dirt.png");
	textures[2] = RENDERER.addTexture("Sand.png");
	textures[3] = RENDERER.addTexture("Snow.png");
	textures[4] = RENDERER.addTexture("Stone.png");
	textures[5] = RENDERER.addTexture("Swamp.png");
	textures[6] = RENDERER.addTexture("Water.png");

	editorWidget->addTexture("Grass");
	editorWidget->addTexture("Dirt");
	editorWidget->addTexture("Sand");
	editorWidget->addTexture("Snow");
	editorWidget->addTexture("Stone");
	editorWidget->addTexture("Swamp");
	editorWidget->addTexture("Water");
}

void MapEditorWindow::keyPressEvent(QKeyEvent* e)
{

}

void MapEditorWindow::keyReleaseEvent(QKeyEvent* e)
{

}

void MapEditorWindow::loadMap()
{
	QString targetFile = QFileDialog::getOpenFileName(this, "Open Map", "Maps", "Map Files (*.map)");
	if(targetFile == "")
		return;

	QFile file(targetFile);
	if(!file.open(QIODevice::ReadOnly))
	{
		qDebug()<<"Error Reading form File: "<<file.fileName();
	}

	QDataStream input(&file);
	
	for(int x = 0; x < MAX_DIMENSION_VALUE; x++)
	{
		for(int y = 0; y < MAX_DIMENSION_VALUE; y++)
		{
			for(int z = 0; z < MAX_DIMENSION_VALUE; z++)
			{
				int stealth;
				int textureID;
				input>>stealth>>textureID;
				cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].IsVisible = stealth;
				cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID = textureID;
			}
		}
	}
}

void MapEditorWindow::loadMapFromImage()
{
	QString targetFile = QFileDialog::getOpenFileName(this, "Open Image", "Images", "Images (*.png *.jpg)");
	if(targetFile == "")
		return;

	QImage file(targetFile);
	if(file.isNull())
	{
		qDebug()<<"Error Reading Image";
	}

	const int mapWidth = mapDimensions->getDimensions().x;
	const int mapLength = mapDimensions->getDimensions().z;
	int xChunk = file.width() / mapWidth;
	int yChunk = file.height() / mapLength;
	QImage *textures = new QImage[mapWidth * mapLength];

	for(int x = 0; x < mapWidth; x++)
	{
		for(int y = 0; y < mapLength; y++)
		{
			int iMax = xChunk * (x + 1);
			textures[x * mapWidth + y] = QImage(xChunk, yChunk, QImage::Format::Format_RGB32);
			for(int i = xChunk * x; i < iMax; i++)
			{
				int jMax = yChunk * (y + 1);
				for(int j = yChunk * y; j < jMax; j++)
				{
					textures[x * mapWidth + y].setPixel(i % xChunk, j % yChunk, file.pixel(i, j));
				}
			}
		}
	}
	textures[0].save("Index 0.png", "PNG", 1);
	textures[1].save("Index 1.png", "PNG", 1);
	textures[2].save("Index 2.png", "PNG", 1);
	textures[3].save("Index 3.png", "PNG", 1);
	textures[4].save("Index 4.png", "PNG", 1);

	for(int x = 0; x < mapWidth; x++)
	{
		for(int y = 0; y < mapLength; y++)
		{
			for(int z = 0; z < 1; z++)
			{
				cubes[x * mapWidth + y] = *RENDERER.addCube(Vector4(), Vector3(x, z, y), RENDERER.addTexture(textures[x * mapWidth + y]), 1, true); 
			}
		}
	}
	delete [] textures;
	qDebug()<<"Done Reading File";
}

void MapEditorWindow::saveMap()
{
	QString targetfile = QFileDialog::getSaveFileName(this, "Save Map", "Maps", "Map Files (*.map)");
	if(targetfile == "")
		return;

	QFile file(targetfile);
	if(!file.open(QIODevice::WriteOnly))
	{
		qDebug()<<"Error Writing to File: "<<file.fileName();
	}

	QDataStream output(&file);

	for(int x = 0; x < MAX_DIMENSION_VALUE; x++)
	{
		for(int y = 0; y < MAX_DIMENSION_VALUE; y++)
		{
			for(int z = 0; z < MAX_DIMENSION_VALUE; z++)
			{
				int stealth = cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].IsVisible;
				int textureID = cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID;
				output<<stealth<<textureID;
			}
		}
	}
}

void MapEditorWindow::saveMapAs()
{

}