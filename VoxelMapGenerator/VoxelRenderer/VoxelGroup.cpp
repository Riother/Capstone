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

			}
		}
	}
}