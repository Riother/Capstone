#include "EditorWidget.h"

EditorWidget::EditorWidget(int maxRow, int maxColumn, int maxHeight)
{
	EditorLayout = new QVBoxLayout;
	ColorLayout = new QVBoxLayout;

	red = new LabeledSpinbox("Red", true, 0, 255, 255);
	green = new LabeledSpinbox("Green", true, 0, 255, 255);
	blue = new LabeledSpinbox("Blue", true, 0, 255, 255);
	alpha = new LabeledSpinbox("Aplha", true, 0, 255, 255);

	column = new LabeledSpinbox("Column", true, 1, maxRow, 1);
	row = new LabeledSpinbox("Row", true, 1, maxColumn, 1);
	desiredHeight = new LabeledSpinbox("Max Height", true, 1, maxHeight, 1);
	currentHeight = new LabeledSpinbox("Current Height", true, 1, maxHeight, 1);
	texture =  new LabeledCombobox("Texture", true);

	ColorLayout->addWidget(red);
	ColorLayout->addWidget(green);
	ColorLayout->addWidget(blue);
	ColorLayout->addWidget(alpha);

	EditorLayout->addLayout(ColorLayout);
	EditorLayout->addWidget(column);
	EditorLayout->addWidget(row);
	EditorLayout->addWidget(desiredHeight);
	EditorLayout->addWidget(currentHeight);
	EditorLayout->addWidget(texture);

	setLayout(EditorLayout);
	setFocusPolicy(Qt::ClickFocus);
	show();

	connect(red, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(green, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(blue, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(alpha, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(column, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(row, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(desiredHeight, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(currentHeight, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(keyUpdate()));
	connect(texture, SIGNAL(currentIndexChanged()), this, SLOT(updateTexture()));
	updateTimer.start(0);
}

EditorWidget::EditorWidget(Vector3 dimensions)
{
	EditorLayout = new QVBoxLayout;
	ColorLayout = new QVBoxLayout;

	red = new LabeledSpinbox("Red", true, 0, 255, 255);
	green = new LabeledSpinbox("Green", true, 0, 255, 255);
	blue = new LabeledSpinbox("Blue", true, 0, 255, 255);
	alpha = new LabeledSpinbox("Aplha", true, 0, 255, 255);

	column = new LabeledSpinbox("Row", true, 1, dimensions.x, 1);
	row = new LabeledSpinbox("Column", true, 1, dimensions.z, 1);
	desiredHeight = new LabeledSpinbox("Height", true, 1, dimensions.y, 1);
	currentHeight = new LabeledSpinbox("Current Height", true, 1, dimensions.y, 1);
	texture =  new LabeledCombobox("Texture", true);

	ColorLayout->addWidget(red);
	ColorLayout->addWidget(green);
	ColorLayout->addWidget(blue);
	ColorLayout->addWidget(alpha);

	EditorLayout->addLayout(ColorLayout);
	EditorLayout->addWidget(column);
	EditorLayout->addWidget(row);
	EditorLayout->addWidget(desiredHeight);
	EditorLayout->addWidget(currentHeight);
	EditorLayout->addWidget(texture);

	setLayout(EditorLayout);
	setFocusPolicy(Qt::ClickFocus);
	show();

	connect(red, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(green, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(blue, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(alpha, SIGNAL(valueChanged()), this, SLOT(updateColors()));
	connect(column, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(row, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(desiredHeight, SIGNAL(valueChanged()), this, SLOT(updateHeight()));
	connect(currentHeight, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(keyUpdate()));
	connect(texture, SIGNAL(currentIndexChanged()), this, SLOT(updateTexture()));
	updateTimer.start(0);
}

void EditorWidget::updateColors()
{
	emit colorChanged();
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
	column->setSpinboxRange(1, newMaxRange);
}

void EditorWidget::updateColumnRange(int newMaxRange)
{
	row->setSpinboxRange(1, newMaxRange);
}

void EditorWidget::updateHeightRange(int newMaxRange)
{
	desiredHeight->setSpinboxRange(1, newMaxRange);
}

void EditorWidget::updateRanges(Vector3 dimensions)
{
	column->setSpinboxRange(1, dimensions.x);
	row->setSpinboxRange(1, dimensions.z);
	desiredHeight->setSpinboxRange(1, dimensions.y);
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
	return Vector2(row->getSpinboxValue() - 1, column->getSpinboxValue() - 1);
}

int EditorWidget::getChosenHeight()
{
	return desiredHeight->getSpinboxValue();
}

int EditorWidget::getCurrentHeight()
{
	return currentHeight->getSpinboxValue();
}

void EditorWidget::setHeight(int newHeight)
{
	desiredHeight->setSpinboxValue(newHeight);
}

void EditorWidget::setCurrentHeightMax(int max)
{
	currentHeight->setMaxRange(max);
}

void EditorWidget::setColors(Vector4 newColors)
{
	red->setSpinboxValue(newColors.x * 255);
	green->setSpinboxValue(newColors.y * 255);
	blue->setSpinboxValue(newColors.z * 255);
	alpha->setSpinboxValue(newColors.w * 255);
}

Vector4 EditorWidget::getColor()
{
	float cRed = (float)red->getSpinboxValue() / 255;
	float cGreen = (float)green->getSpinboxValue() / 255;
	float cBlue = (float)blue->getSpinboxValue() / 255;
	float cAlpha = (float)alpha->getSpinboxValue() / 255;
	return Vector4(cRed, cGreen, cBlue, cAlpha);
}

void EditorWidget::keyUpdate()
{
}

void EditorWidget::keyPressEvent(QKeyEvent* e)
{
	if(e->key() == Qt::Key_Down && column->getSpinboxValue() + 1 <= column->getMaxRange()) 
	{
		column->setSpinboxValue(column->getSpinboxValue() + 1);
	}
	else if(e->key() == Qt::Key_Up && column->getSpinboxValue() - 1 >= column->getMinRange()) 
	{
		column->setSpinboxValue(column->getSpinboxValue() - 1);
	}

	if(e->key() == Qt::Key_Right && row->getSpinboxValue() + 1 <= row->getMaxRange())
	{
		row->setSpinboxValue(row->getSpinboxValue() + 1);
	}
	else if(e->key() == Qt::Key_Left && row->getSpinboxValue() - 1 >= row->getMinRange())
	{
		row->setSpinboxValue(row->getSpinboxValue() - 1);
	}

	if(e->key() == Qt::Key_Back && desiredHeight->getSpinboxValue() - 1 >= desiredHeight->getMinRange())
	{
		desiredHeight->setSpinboxValue(desiredHeight->getSpinboxValue() - 1);
	}
	else if(e->key() == Qt::Key_Forward && desiredHeight->getSpinboxValue() + 1 <= desiredHeight->getMaxRange())
	{
		desiredHeight->setSpinboxValue(desiredHeight->getSpinboxValue() + 1);
	}
	 

	if(e->key() == Qt::Key_1)
	{
		desiredHeight->setSpinboxValue(1);
	}
	else if(e->key() == Qt::Key_2)
	{
		desiredHeight->setSpinboxValue(2);
	}
	else if(e->key() == Qt::Key_3)
	{
		desiredHeight->setSpinboxValue(3);
	}
	else if(e->key() == Qt::Key_4)
	{
		desiredHeight->setSpinboxValue(4);
	}
	else if(e->key() == Qt::Key_5)
	{
		desiredHeight->setSpinboxValue(5);
	}
	else if(e->key() == Qt::Key_6)
	{
		desiredHeight->setSpinboxValue(6);
	}
	else if(e->key() == Qt::Key_7)
	{
		desiredHeight->setSpinboxValue(7);
	}
	else if(e->key() == Qt::Key_8)
	{
		desiredHeight->setSpinboxValue(8);
	}
	else if(e->key() == Qt::Key_9)
	{
		desiredHeight->setSpinboxValue(9);
	}
	else if(e->key() == Qt::Key_0)
	{
		desiredHeight->setSpinboxValue(10);
	}
}