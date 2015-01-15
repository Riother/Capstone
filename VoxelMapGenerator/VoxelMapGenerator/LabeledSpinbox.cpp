#include "LabeledSpinbox.h"

LabeledSpinbox::LabeledSpinbox(const char* labelText, bool textOnLeft, int minRange, int maxRange, int value)
{
	QLayout* layout = textOnLeft ? (QLayout*) new QHBoxLayout : new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(label = new QLabel);
	label->setText(labelText);
	label->setMinimumWidth(35);
	label->setAlignment(Qt::AlignCenter);

	layout->addWidget(spinbox = new QSpinBox);
	spinbox->setValue(value);
	spinbox->setRange(minRange, maxRange);
	connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(spinboxValueChanged()));
	spinboxValueChanged();
}

void LabeledSpinbox::setValue(int newValue)
{
	spinbox->setValue(newValue);
}

int LabeledSpinbox::getValue()
{
	return spinbox->value();
}

void LabeledSpinbox::setRange(int min, int max)
{
	spinbox->setRange(min, max);
}

void LabeledSpinbox::spinboxValueChanged()
{
	emit valueChanged();
}