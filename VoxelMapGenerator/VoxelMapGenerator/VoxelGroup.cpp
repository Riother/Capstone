#include "VoxelGroup.h"

VoxelGroup::VoxelGroup(Vector3 position, GeometryInfo* cube, ShaderInfo* shader)
{
	Position = position;
	
	for(int x = 0; x < DIMENSIONS; x++)
	{
		for(int y = 0; y < DIMENSIONS; y++)
		{
			for(int z = 0; z < DIMENSIONS; z++)
			{
				Matrix4 mat = (glm::translate(Vector3(x, y, z))) * glm::scale(Vector3(0.5f, 0.5f, 0.5f));
				
				if(y > 1 && (x != 1 && x != 3))
					IsVisible = true;
				else
					IsVisible = false;

				Cube = cube;
				Shader = shader;
				RENDERER.addRenderable(Cube, mat, Shader, IsVisible, Vector4(0, 1, 0, 1), -1, false);
			}
		}
	}
}