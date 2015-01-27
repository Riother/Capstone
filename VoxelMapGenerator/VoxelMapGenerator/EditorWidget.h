#ifndef EDITOR_WIDGET_H
#define EDITOR_WIDGET_H

#include <GL\glew.h>
#include <QtGui\qwidget.h>
#include <Qt\qmainwindow.h>
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <qt\qboxlayout.h>
#include <glm\glm.hpp>
#include <QtGui\qkeyevent>
#include <Qt\qtimer.h>
#include <Qt\qdebug.h>
//#include <Windows.h>
#include "LabeledSpinbox.h"
#include "LabeledComboBox.h"

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
	LabeledCombobox* texture;
	GLuint textures[7];
	QTimer updateTimer;
	void loadTextures();
private slots:
		void updateSpinboxes();
		void updateHeight();
		void keyUpdate();
		void updateTexture();
signals:
		void valueChanged();
		void currentIndexChanged();
		void heightChanged();
public:
	EditorWidget(int maxRow, int maxColumn, int maxHeight);
	EditorWidget(Vector3 dimensions);
	void updateRowRange(int newMaxRange);
	void updateColumnRange(int newMaxRange);
	void updateHeightRange(int newMaxRange);
	void updateRanges(Vector3 dimensions);
	void addTexture(const char* texture);
	int getTexture();
	Vector2 getPosition();
	int getChosenHeight();
	void setHeight(int newHeight);
protected:
	void keyPressEvent(QKeyEvent* e);
};

#endif