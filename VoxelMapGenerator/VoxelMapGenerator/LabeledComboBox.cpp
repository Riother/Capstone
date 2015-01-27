#include "LabeledComboBox.h"

LabeledCombobox::LabeledCombobox(const char* labelText, bool textOnLeft)
{
	QLayout* layout = textOnLeft ? (QLayout*) new QHBoxLayout : new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(label = new QLabel);
	label->setText(labelText);
	label->setMinimumWidth(35);
	label->setAlignment(Qt::AlignCenter);

	layout->addWidget(combobox = new QComboBox);
	combobox->addItem("No Texture");
	connect(combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxValueChanged()));
	comboboxValueChanged();
}

void LabeledCombobox::addItem(const char* item)
{
	combobox->addItem(item);
}

int LabeledCombobox::getCurrentIndex()
{
	
	return combobox->currentIndex() == 0 ? -1 : combobox->currentIndex();
}

void LabeledCombobox::comboboxValueChanged()
{
	emit currentIndexChanged();
}