#ifndef MAP_EDITOR_WINDOW_H
#define MAP_EDITOR_WINDOW_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <Qt\qaction.h>
#include <QtGui\qfiledialog.h>
#include <Qt\qtimer.h>
#include "RendererWindow.h"
#include "ParameterType.h"
#include "Cube.h"
#include "ShapeData.h"
#include "ShapeGenerator.h"
#include "LabeledSpinbox.h"
#include "MapDimensionsWidget.h"
#include "EditorWidget.h"
#include "VoxelGroup.h"
#include "Voxel.h"
#include "fstream"
#include "iostream"

using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;

class MapEditorWindow : public QMainWindow
{
private:
	QTimer timer;
	Q_OBJECT

	static const int MAX_CUBES = 5000;
	static const int MAX_DIMENSION_VALUE = 10;

	QWidget* mainWidget;
	QTabWidget* tabWidget;

	QHBoxLayout* mainLayout;
	QVBoxLayout* tabsLayout;
	QVBoxLayout* rendererLayout;
	MapDimensionsWidget* mapDimensions;
	EditorWidget* editorWidget;
	Cube cube;
	GeometryInfo* cubeInfo;
	ShaderInfo* shaderInfo;
	Voxel cubes[MAX_CUBES];
	GLuint textures[7];
	VoxelGroup* voxels;
	int cubeCount;
	bool isVisible;
private slots:
	void saveMapAs();
	void saveMap();
	void loadMap();
	void loadMapFromImage();
	void updateLoop();
	void updateHeight();
signals:
	void triggered();
public:
	MapEditorWindow();
	void prepareAssets();
protected:
	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif