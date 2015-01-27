#include "Voxel.h"

Voxel::Voxel(GLuint textureID, bool isVisible, int x, int y, int z)
{
	TextureID = textureID;
	IsVisible = isVisible;
	Color = Vector4(0, 0, 0, 1);
	Position = Vector3();
}

Voxel::Voxel()
{
	TextureID = 0;
	IsVisible = true;
	Color = Vector4(0, 0, 0, 1);
}