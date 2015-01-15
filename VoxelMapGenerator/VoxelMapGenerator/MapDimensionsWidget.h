#ifndef MAP_DIMENSIONS_WIDGET_H
#define MAP_DIMENSIONS_WIDGET_H

#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <Qt\qboxlayout.h>
#include <glm\glm.hpp>
#include "LabeledSpinbox.h"

typedef glm::vec3 Vector3;

class MapDimensionsWidget : public QWidget
{
	Q_OBJECT
	int TabIndex;
	QVBoxLayout* DimensionsLayout;
	QWidget* DimensionsWidget;
	LabeledSpinbox* length;
	LabeledSpinbox* width;
	LabeledSpinbox* height;
	LabeledSpinbox* cameraSpeed;
private slots:
	void updateSpinboxes();
signals:
	void valueChanged();
public:
	MapDimensionsWidget();
	Vector3 getDimensions();
	int getCameraSpeed();
};

#endif