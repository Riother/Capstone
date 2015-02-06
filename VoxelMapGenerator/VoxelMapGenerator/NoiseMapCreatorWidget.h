#ifndef NOISE_MAP_CREATOR_WIDGET_H
#define NOISE_MAP_CREATOR_WIDGET_H

#include <QtGui\qwidget.h>
#include <QtGui\qboxlayout.h>
#include <Qt\qtimer.h>
#include "LabeledSpinbox.h"
#include <noise\noise.h>
///#include "noiseutils.h"

class NoiseMapCreatorWidget : public QWidget
{
	Q_OBJECT
	QVBoxLayout* NoiseLayout;
	noise::module::Perlin perlinModule;
	//utils::NoiseMap heightMap;
	//utils::NoiseMapBuilderPlane heightMapBuilder;
	LabeledSpinbox* ImageSize;
	LabeledSpinbox* ColorScale;
	QTimer updateTimer;
	float octave;
	float frequency;
private slots:
	void updateNoise();
signals:
	void valueChanged();
public:
	NoiseMapCreatorWidget();
};

#endif