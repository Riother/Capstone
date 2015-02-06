#include <GL\glew.h>
#include "NoiseMapCreatorWidget.h"

NoiseMapCreatorWidget::NoiseMapCreatorWidget()
{
	NoiseLayout =  new QVBoxLayout;

	setLayout(NoiseLayout);
	show();

	//heightMapBuilder.SetSourceModule(perlinModule);
	//heightMapBuilder.SetDestNoiseMap(heightMap);
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateNoise()));
	updateTimer.start(0);
}

void NoiseMapCreatorWidget::updateNoise()
{
	//heightMapBuilder.SetDestSize(ImageSize->getValue(), ImageSize->getValue());
	///heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	//heightMapBuilder.Build();

}