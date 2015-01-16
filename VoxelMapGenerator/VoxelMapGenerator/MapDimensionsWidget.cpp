#include "MapDimensionsWidget.h"

MapDimensionsWidget::MapDimensionsWidget()
{
	DimensionsLayout = new QVBoxLayout;

	cameraSpeed = new LabeledSpinbox("Camera Speed", true, 1, 100, 10); 
	length = new LabeledSpinbox("Length", true, 1, 10, 10);
	width  = new LabeledSpinbox("Width", true, 1, 10, 10);
	height = new LabeledSpinbox("Height", true, 1, 10, 10);

	DimensionsLayout->addWidget(cameraSpeed);
	DimensionsLayout->addWidget(length);
	DimensionsLayout->addWidget(width);
	DimensionsLayout->addWidget(height);

	setLayout(DimensionsLayout);
	show();

	connect(cameraSpeed, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(length, SIGNAL(valueChanged()),  this, SLOT(updateSpinboxes()));
	connect(width, SIGNAL(valueChanged()),  this, SLOT(updateSpinboxes()));
	connect(height, SIGNAL(valueChanged()),  this, SLOT(updateSpinboxes()));
}

void MapDimensionsWidget::updateSpinboxes()
{
	emit valueChanged();
}

Vector3 MapDimensionsWidget::getDimensions()
{
	return Vector3(width->getValue(), height->getValue(), length->getValue());
}

int MapDimensionsWidget::getCameraSpeed()
{
	return cameraSpeed->getValue();
}
