#include "MapDimensionsWidget.h"

MapDimensionsWidget::MapDimensionsWidget()
{
	DimensionsLayout = new QVBoxLayout;

	cameraSpeed = new LabeledSpinbox("Camera Speed", true, 1, 100, 10); 
	length = new LabeledSpinbox("Length", true, 1, 100, 10);
	width  = new LabeledSpinbox("Width", true, 1, 100, 10);
	maxHeight = new LabeledSpinbox("Max Height", true, 1, 100, 10);

	DimensionsLayout->addWidget(cameraSpeed);
	DimensionsLayout->addWidget(length);
	DimensionsLayout->addWidget(width);
	DimensionsLayout->addWidget(maxHeight);

	setLayout(DimensionsLayout);
	show();

	connect(cameraSpeed, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(length, SIGNAL(valueChanged()),  this, SLOT(updateSpinboxes()));
	connect(width, SIGNAL(valueChanged()),  this, SLOT(updateSpinboxes()));
	connect(maxHeight, SIGNAL(valueChanged()),  this, SLOT(updateSpinboxes()));
}

void MapDimensionsWidget::updateSpinboxes()
{
	length->setMinRange(width->getSpinboxValue());
	emit spinboxValueChanged();
}

Vector3 MapDimensionsWidget::getDimensions()
{
	return Vector3(width->getSpinboxValue(), maxHeight->getSpinboxValue(), length->getSpinboxValue());
}

int MapDimensionsWidget::getCameraSpeed()
{
	return cameraSpeed->getSpinboxValue();
}

int MapDimensionsWidget::getMaxHeight()
{
	return maxHeight->getSpinboxValue();
}