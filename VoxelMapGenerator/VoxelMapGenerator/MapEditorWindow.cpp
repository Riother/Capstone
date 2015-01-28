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

	fileMenu = menuBar()->addMenu("File");

	actionCount = 0;
	QAction* action;
	fileMenu->addAction(action = new QAction("New Project", this));
	action->setShortcut(QKeySequence::New);
	connect(action, SIGNAL(triggered()), this, SLOT(newProject()));
	actionCount++;

	fileMenu->addAction(action = new QAction("Open Project", this));
	action->setShortcut(QKeySequence::Open);
	connect(action, SIGNAL(triggered()), this, SLOT(openProject()));
	actionCount++;

	fileMenu->addAction(action = new QAction("Save Map", this));
	action->setShortcut(QKeySequence::Save);
	action->setDisabled(true);
	connect(action, SIGNAL(triggered()), this, SLOT(saveMap()));
	actionCount++;

	fileMenu->addAction(action = new QAction("Save Map As...", this));
	action->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
	action->setDisabled(true);
	connect(action, SIGNAL(triggered()), this, SLOT(saveMapAs()));
	actionCount++;

	fileMenu->addAction(action = new QAction("Load Map", this));
	action->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
	action->setDisabled(true);
	connect(action, SIGNAL(triggered()), this, SLOT(loadMap()));
	actionCount++;

	fileMenu->addAction(action = new QAction("Load Map From Image", this));
	action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
	action->setDisabled(true);
	connect(action, SIGNAL(triggered()), this, SLOT(loadMapFromImage()));
	actionCount++;

	fileMenu->addAction(action = new QAction("Load Texture", this));
	action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
	action->setDisabled(true);
	connect(action, SIGNAL(triggered()), this, SLOT(loadTexture()));
	actionCount++;

	setCentralWidget(mainWidget);
	show();

	//RENDERER.show();
	prepareAssets();
	editorWidget->setDisabled(true);
	mapDimensions->setDisabled(true);
	RENDERER.setDisabled(true);

	connect(mapDimensions, SIGNAL(valueChanged()), this, SLOT(updateLoop()));
	connect(editorWidget, SIGNAL(valueChanged()), this, SLOT(updateLoop()));
	connect(editorWidget, SIGNAL(currentIndexChanged()), this, SLOT(updateLoop()));
	connect(editorWidget, SIGNAL(heightChanged()), this, SLOT(updateHeight()));
	//connect(&timer, SIGNAL(timeout()), this, SLOT(updateLoop()));
}

void MapEditorWindow::newProject()
{
	//bool hasInput;
	//QString directoryName = QInputDialog::getText(this, "Creating New Project", "Project Name:", QLineEdit::Normal, QDir::home().dirName(), &hasInput);  
	QString directoryName = QFileDialog::getExistingDirectory(this, "Create Project", "/Home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(!directoryName.isEmpty()) 
	{
		projectDirectory = QDir(directoryName);
		if(!QDir(projectDirectory.path() + "/Maps").exists())
		{
			projectDirectory.mkdir("Maps");
		}
		if(!QDir(projectDirectory.path() + "/Textures").exists())
		{
			projectDirectory.mkdir("Textures");
			QImage grass("Grass.png");
			grass.save(projectDirectory.path() + "/Textures/" + "Grass.png");

			QImage dirt("Dirt.png");
			dirt.save(projectDirectory.path() + "/Textures/" + "Dirt.png");

			QImage sand("Sand.png");
			sand.save(projectDirectory.path() + "/Textures/" + "Sand.png");

			QImage snow("Snow.png");
			snow.save(projectDirectory.path() + "/Textures/" + "Snow.png");

			QImage stone("Stone.png");
			stone.save(projectDirectory.path() + "/Textures/" + "Stone.png");

			QImage swamp("Swamp.png");
			swamp.save(projectDirectory.path() + "/Textures/" + "Swamp.png");

			QImage water("Water.png");
			water.save(projectDirectory.path() + "/Textures/" + "Water.png");
		}

		if(!QDir(projectDirectory.path() + "/Images").exists())
		{
			projectDirectory.mkdir("Images");
		}

		editorWidget->setDisabled(false);
		mapDimensions->setDisabled(false);
		for(int i = 0; i < actionCount; i++)
		{
			fileMenu->actions().at(i)->setDisabled(false);
		}
		RENDERER.setDisabled(false);
	}
	//QString directory = QFileDialog::getExistingDirectory(this, "Create Project", "/Home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

void MapEditorWindow::openProject()
{
	QString directoryName = QFileDialog::getExistingDirectory(this, "Open Existing Project", "/Home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(!directoryName.isEmpty())
	{
		projectDirectory = QDir(directoryName);
		QStringList allTextures = QDir(directoryName + "/Textures").entryList(QDir::Files, QDir::NoSort);
		int textureCount = allTextures.count();
		RENDERER.setDisabled(false);
		for(int i = 0; i < textureCount; i++)
		{
			QByteArray filePath = QString(projectDirectory.path() + "/Textures/" + allTextures.at(i)).toUtf8();
			QByteArray fileName = allTextures.at(i).toUtf8();
			editorWidget->addTexture(fileName.constData());
			textures.append(RENDERER.addTexture(filePath.constData()));
			//qDebug()<<QDir(directoryName + "/Textures").entryList(QDir::Files, QDir::NoSort).at(i);
		}

		editorWidget->setDisabled(false);
		mapDimensions->setDisabled(false);
		for(int i = 0; i < actionCount; i++)
		{
			fileMenu->actions().at(i)->setDisabled(false);
		}
	}
}

void MapEditorWindow::updateLoop()
{
	int width = mapDimensions->getDimensions().x;
	int length = mapDimensions->getDimensions().z;

	int chosenX = editorWidget->getPosition().x;
	int chosenY = editorWidget->getPosition().y;
	int index = chosenX * width + chosenY;
	editorWidget->setHeight(cubes[chosenX * width + chosenY].Height);
	cubes[index].TextureID = editorWidget->getTexture() == -1 ? editorWidget->getTexture() : textures.at(editorWidget->getTexture());


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
	RENDERER.updateCubes(index, cubes[index]);
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
	
	////Textures
	//textures[0] = RENDERER.addTexture("Grass.png");
	//textures[1] = RENDERER.addTexture("Dirt.png");
	//textures[2] = RENDERER.addTexture("Sand.png");
	//textures[3] = RENDERER.addTexture("Snow.png");
	//textures[4] = RENDERER.addTexture("Stone.png");
	//textures[5] = RENDERER.addTexture("Swamp.png");
	//textures[6] = RENDERER.addTexture("Water.png");

	//editorWidget->addTexture("Grass");
	//editorWidget->addTexture("Dirt");
	//editorWidget->addTexture("Sand");
	//editorWidget->addTexture("Snow");
	//editorWidget->addTexture("Stone");
	//editorWidget->addTexture("Swamp");
	//editorWidget->addTexture("Water");
}

void MapEditorWindow::keyPressEvent(QKeyEvent* e)
{

}

void MapEditorWindow::keyReleaseEvent(QKeyEvent* e)
{

}

void MapEditorWindow::loadMap()
{
	QString targetFile = QFileDialog::getOpenFileName(this, "Open Map", projectDirectory.path() + "/Maps", "Map Files (*.map)");
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
	QString targetFile = QFileDialog::getOpenFileName(this, "Open Image", projectDirectory.path() + "/Images", "Images (*.png)");
	if(targetFile == "")
		return;

	QImage file(targetFile);
	if(file.isNull())
	{
		qDebug()<<"Error Reading Image: "<<targetFile.section('/', -1);
	}
	
	file.save(projectDirectory.path() + "/Images/" + targetFile.section('/', -1));

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
	
	qDebug()<<"Done Reading File: "<<targetFile.section('/', -1);
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

	QFile texturesFile("Textures.textures");
	if(!file.open(QIODevice::WriteOnly))
	{
		qDebug()<<"Error Writing to File: "<<texturesFile.fileName();
	}

	QDataStream texturesOutput(&texturesFile);
	for(int x = 0; x < sizeof(textures) / sizeof(GLuint); x++)
	{
		for(int y = 0; y < MAX_DIMENSION_VALUE; y++)
		{
			for(int z = 0; z < MAX_DIMENSION_VALUE; z++)
			{
				int stealth = cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].IsVisible;
				int textureID = cubes[x * MAX_DIMENSION_VALUE * MAX_DIMENSION_VALUE + y * MAX_DIMENSION_VALUE + z].TextureID;
				texturesOutput<<stealth<<textureID;
			}
		}
	}
	
}

void MapEditorWindow::loadTexture()
{
	QString targetFile = QFileDialog::getOpenFileName(this, "Open Image", projectDirectory.path() + "/Images", "Images (*.png)");
	if(targetFile == "")
		return;

	QImage file(targetFile);
	if(file.isNull())
	{
		qDebug()<<"Error Reading Image: "<<targetFile.section('/', -1);
	}
	file.save(projectDirectory.path() + "/Textures/" + targetFile.section('/', -1));
	QByteArray byteArray = targetFile.toUtf8();
	editorWidget->addTexture(byteArray.constData());
	textures.append(RENDERER.addTexture(byteArray.constData()));
}

void MapEditorWindow::saveMapAs()
{

}