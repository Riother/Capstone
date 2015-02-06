#include "Voxel.h"

const int MAX_HEIGHT = 100;

Voxel::Voxel(Vector4 color, Vector3 position, GLuint textureID, int height, bool isVisible)
{
	TextureID.append(textureID);
	IsVisible.append(isVisible);
	Color.append(color);
	Position = position;
	Height = 1;
}

Voxel::Voxel()
{
	TextureID.append(-1);
	IsVisible.append(true);
	Color.append(Vector4(0.5f, 0.5f, 0.5f, 1));
	Height = 1;
}