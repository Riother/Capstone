#ifndef LABELED_SPINBOX_H
#define LABELED_SPINBOX_H
#include <Qt\qlabel.h>
#include <Qt\qspinbox.h>
#include <QtGui\qvboxlayout>

class LabeledSpinbox : public QWidget
{
	Q_OBJECT
	QLabel* label;
	QSpinBox* spinbox;
	private slots:
		void spinboxValueChanged();
signals:
	void valueChanged();
public:
	LabeledSpinbox(const char* labelText, bool textOnLeft, int minRange, int maxRange, int value = 0);
	void setValue(int newValue);
	int getValue();
	void setRange(int min, int max);
};

#endif