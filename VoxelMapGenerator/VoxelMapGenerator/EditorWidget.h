#ifndef EDITOR_WIDGET_H
#define EDITOR_WIDGET_H

#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <qt\qboxlayout.h>
#include <glm\glm.hpp>
#include "LabeledSpinbox.h"

typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;

class EditorWidget : public QWidget
{
	Q_OBJECT
	int TabIndex;
	QVBoxLayout* EditorLayout;
	LabeledSpinbox* row;
	LabeledSpinbox* column;
	LabeledSpinbox* desiredHeight;
private slots:
		void updateSpinboxes();
signals:
		void valueChanged();
public:
	EditorWidget(int maxRow, int maxColumn, int maxHeight);
	EditorWidget(Vector3 dimensions);
	void updateRowRange(int newMaxRange);
	void updateColumnRange(int newMaxRange);
	void updateHeightRange(int newMaxRange);
	void updateRanges(Vector3 dimensions);
	Vector2 getPosition();
	int getChosenHeight();
};

#endif