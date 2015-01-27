#ifndef LABELED_COMBOBOX_H
#define LABELED_COMBOBOX_H
#include <Qt\qlabel.h>
#include <Qt\qcombobox.h>
#include <QtGui\qvboxlayout>

class LabeledCombobox : public QWidget
{
	Q_OBJECT
	QLabel* label;
	QComboBox* combobox;
	private slots:
		void comboboxValueChanged();
signals:
	void currentIndexChanged();
public:
	LabeledCombobox(const char* labelText, bool textOnLeft);
	
	int getCurrentIndex();
	void addItem(const char* text);
};

#endif