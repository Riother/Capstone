#include "Voxel.h"

Voxel::Voxel(Vector4 color, Vector3 position, GLuint textureID, int height, bool isVisible)
{
	TextureID = textureID;
	IsVisible = isVisible;
	Color = Vector4(0, 0, 0, 1);
	Position = Vector3(position.x, position.y, position.z);
	Height = height;
}

Voxel::Voxel()
{
	TextureID = 0;
	IsVisible = true;
	Color = Vector4(0, 0, 0, 1);
	Height = 1;
}