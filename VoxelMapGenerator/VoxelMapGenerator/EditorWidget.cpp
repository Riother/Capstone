#include "EditorWidget.h"

EditorWidget::EditorWidget(int maxRow, int maxColumn, int maxHeight)
{
	EditorLayout = new QVBoxLayout;

	column = new LabeledSpinbox("Column", true, 1, maxRow, 1);
	row = new LabeledSpinbox("Row", true, 1, maxColumn, 1);
	desiredHeight = new LabeledSpinbox("Height", true, 1, maxHeight, 1);
	texture =  new LabeledCombobox("Texture", true);

	EditorLayout->addWidget(column);
	EditorLayout->addWidget(row);
	EditorLayout->addWidget(desiredHeight);
	EditorLayout->addWidget(texture);

	setLayout(EditorLayout);
	setFocusPolicy(Qt::ClickFocus);
	show();

	connect(column, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(row, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(desiredHeight, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(keyUpdate()));
	connect(texture, SIGNAL(currentIndexChanged()), this, SLOT(updateTexture()));
	updateTimer.start(0);
}

EditorWidget::EditorWidget(Vector3 dimensions)
{
	EditorLayout = new QVBoxLayout;

	column = new LabeledSpinbox("Row", true, 1, dimensions.x, 1);
	row = new LabeledSpinbox("Column", true, 1, dimensions.z, 1);
	desiredHeight = new LabeledSpinbox("Height", true, 1, dimensions.y, 1);
	texture =  new LabeledCombobox("Texture", true);

	EditorLayout->addWidget(column);
	EditorLayout->addWidget(row);
	EditorLayout->addWidget(desiredHeight);
	EditorLayout->addWidget(texture);

	setLayout(EditorLayout);
	setFocusPolicy(Qt::ClickFocus);
	show();

	connect(column, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(row, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(desiredHeight, SIGNAL(valueChanged()), this, SLOT(updateHeight()));
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(keyUpdate()));
	connect(texture, SIGNAL(currentIndexChanged()), this, SLOT(updateTexture()));
	updateTimer.start(0);
}

void EditorWidget::updateSpinboxes()
{
	emit valueChanged();
}

void EditorWidget::updateHeight()
{
	emit heightChanged();
}

void EditorWidget::updateTexture()
{
	emit currentIndexChanged();
}

void EditorWidget::updateRowRange(int newMaxRange)
{
	column->setRange(1, newMaxRange);
}

void EditorWidget::updateColumnRange(int newMaxRange)
{
	row->setRange(1, newMaxRange);
}

void EditorWidget::updateHeightRange(int newMaxRange)
{
	desiredHeight->setRange(1, newMaxRange);
}

void EditorWidget::updateRanges(Vector3 dimensions)
{
	column->setRange(1, dimensions.x);
	row->setRange(1, dimensions.z);
	desiredHeight->setRange(1, dimensions.y);
}

void EditorWidget::addTexture(const char* texture)
{
	this->texture->addItem(texture);
}

int EditorWidget::getTexture()
{
	return texture->getCurrentIndex();
}

Vector2 EditorWidget::getPosition()
{
	return Vector2(row->getValue() - 1, column->getValue() - 1);
}

int EditorWidget::getChosenHeight()
{
	return desiredHeight->getValue();
}

void EditorWidget::setHeight(int newHeight)
{
	desiredHeight->setValue(newHeight);
}

void EditorWidget::keyUpdate()
{
}

void EditorWidget::keyPressEvent(QKeyEvent* e)
{
	if(e->key() == Qt::Key_S && column->getValue() + 1 <= 10) 
	{
		column->setValue(column->getValue() + 1);
	}
	else if(e->key() == Qt::Key_W && column->getValue() - 1 >= 1) 
	{
		column->setValue(column->getValue() - 1);
	}

	if(e->key() == Qt::Key_D && row->getValue() + 1 <= 10)
	{
		row->setValue(row->getValue() + 1);
	}
	else if(e->key() == Qt::Key_A && row->getValue() - 1 >= 1)
	{
		row->setValue(row->getValue() - 1);
	}

	if(e->key() == Qt::Key_1)
	{
		desiredHeight->setValue(1);
	}
	else if(e->key() == Qt::Key_2)
	{
		desiredHeight->setValue(2);
	}
	else if(e->key() == Qt::Key_3)
	{
		desiredHeight->setValue(3);
	}
	else if(e->key() == Qt::Key_4)
	{
		desiredHeight->setValue(4);
	}
	else if(e->key() == Qt::Key_5)
	{
		desiredHeight->setValue(5);
	}
	else if(e->key() == Qt::Key_6)
	{
		desiredHeight->setValue(6);
	}
	else if(e->key() == Qt::Key_7)
	{
		desiredHeight->setValue(7);
	}
	else if(e->key() == Qt::Key_8)
	{
		desiredHeight->setValue(8);
	}
	else if(e->key() == Qt::Key_9)
	{
		desiredHeight->setValue(9);
	}
	else if(e->key() == Qt::Key_0)
	{
		desiredHeight->setValue(10);
	}
}