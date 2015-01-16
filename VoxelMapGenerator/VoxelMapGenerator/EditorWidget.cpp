#include "EditorWidget.h"

EditorWidget::EditorWidget(int maxRow, int maxColumn, int maxHeight)
{
	EditorLayout = new QVBoxLayout;

	column = new LabeledSpinbox("Column", true, 1, maxRow, 1);
	row = new LabeledSpinbox("Row", true, 1, maxColumn, 1);
	desiredHeight = new LabeledSpinbox("Height", true, 1, maxHeight, 1);

	EditorLayout->addWidget(column);
	EditorLayout->addWidget(row);
	EditorLayout->addWidget(desiredHeight);

	setLayout(EditorLayout);
	show();

	connect(column, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(row, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(desiredHeight, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
}

EditorWidget::EditorWidget(Vector3 dimensions)
{
	EditorLayout = new QVBoxLayout;

	column = new LabeledSpinbox("Row", true, 1, dimensions.x, 1);
	row = new LabeledSpinbox("Column", true, 1, dimensions.z, 1);
	desiredHeight = new LabeledSpinbox("Height", true, 1, dimensions.y, 1);

	EditorLayout->addWidget(column);
	EditorLayout->addWidget(row);
	EditorLayout->addWidget(desiredHeight);

	setLayout(EditorLayout);
	show();

	connect(column, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(row, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
	connect(desiredHeight, SIGNAL(valueChanged()), this, SLOT(updateSpinboxes()));
}

void EditorWidget::updateSpinboxes()
{
	emit valueChanged();
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

Vector2 EditorWidget::getPosition()
{
	return Vector2(row->getValue() - 1, column->getValue() - 1);
}

int EditorWidget::getChosenHeight()
{
	return desiredHeight->getValue();
}

