#ifndef MAP_EDITOR_WINDOW_H
#define MAP_EDITOR_WINDOW_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qmenu.h>
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

class MapEditorWindow : public QMainWindow
{
private:
	QTimer timer;
	Q_OBJECT

	static const int MAX_RENDERABLES = 1000;
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
	RenderableInfo* cubeRenderables[MAX_RENDERABLES];
	VoxelGroup* voxels;
	bool isVisible;
private slots:
	void updateLoop();
public:
	MapEditorWindow();
	void createMap();
};

#endif