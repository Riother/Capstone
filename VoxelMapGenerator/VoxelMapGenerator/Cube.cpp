#include "Cube.h"

Cube::Cube()
{
	createCubeVerticesAndColor();
	createCubeIndices();
}

void Cube::createCubeVerticesAndColor()
{
	//Top
	vertices[0]  = Vector3(-1.0f, +1.0f, +1.0f); // 0
	vertices[1]  = Vector3(+1.0f, +0.0f, +0.0f); // Color
	vertices[2]  = Vector3(+0.0f, +1.0f, +0.0f); // Normal
	vertices[3]  = Vector3(+0.0f, +1.0f, +0.0f); // UV
	vertices[4]  = Vector3(+1.0f, +1.0f, +1.0f); // 1
	vertices[5]  = Vector3(+0.0f, +1.0f, +0.0f); // Color
	vertices[6]  = Vector3(+0.0f, +1.0f, +0.0f); // Normal
	vertices[7]  = Vector3(+1.0f, +1.0f, +0.0f); // UV
	vertices[8]  = Vector3(+1.0f, +1.0f, -1.0f); // 2
	vertices[9]  = Vector3(+0.0f, +0.0f, +1.0f); // Color
	vertices[10] = Vector3(+0.0f, +1.0f, +0.0f); // Normal
	vertices[11] = Vector3(+1.0f, +0.0f, +0.0f); // UV
	vertices[12] = Vector3(-1.0f, +1.0f, -1.0f); // 3
	vertices[13] = Vector3(+1.0f, +1.0f, +1.0f); // Color
	vertices[14] = Vector3(+0.0f, +1.0f, +0.0f); // Normal
	vertices[15] = Vector3(+0.0f, +0.0f, +0.0f); // UV
	
	//Front
	vertices[16] = Vector3(-1.0f, +1.0f, -1.0f); // 4
	vertices[17] = Vector3(+1.0f, +0.0f, +1.0f); // Color
	vertices[18] = Vector3(+0.0f, +0.0f, +1.0f); // Normal
	vertices[19] = Vector3(+0.0f, +1.0f, +0.0f); // UV
	vertices[20] = Vector3(+1.0f, +1.0f, -1.0f); // 5
	vertices[21] = Vector3(+0.0f, +0.5f, +0.2f); // Color
	vertices[22] = Vector3(+0.0f, +0.0f, +1.0f); // Normal
	vertices[23] = Vector3(+1.0f, +1.0f, +0.0f); // UV
	vertices[24] = Vector3(+1.0f, -1.0f, -1.0f); // 6
	vertices[25] = Vector3(+0.8f, +0.6f, +0.4f); // Color
	vertices[26] = Vector3(+0.0f, +0.0f, +1.0f); // Normal
	vertices[27] = Vector3(+1.0f, +0.0f, +0.0f); // UV
	vertices[28] = Vector3(-1.0f, -1.0f, -1.0f); // 7
	vertices[29] = Vector3(+0.3f, +1.0f, +0.5f); // Color
	vertices[30] = Vector3(+0.0f, +0.0f, +1.0f); // Normal
	vertices[31] = Vector3(+0.0f, +0.0f, +0.0f); // UV
	
	//Right
	vertices[32] = Vector3(+1.0f, +1.0f, -1.0f); // 8
	vertices[33] = Vector3(+0.2f, +0.5f, +0.2f); // Color
	vertices[34] = Vector3(+1.0f, +0.0f, +0.0f); // Normal
	vertices[35] = Vector3(+0.0f, +1.0f, +0.0f); // UV
	vertices[36] = Vector3(+1.0f, +1.0f, +1.0f); // 9
	vertices[37] = Vector3(+0.9f, +0.3f, +0.7f); // Color
	vertices[38] = Vector3(+1.0f, +0.0f, +0.0f); // Normal
	vertices[39] = Vector3(+1.0f, +1.0f, +0.0f); // UV
	vertices[40] = Vector3(+1.0f, -1.0f, +1.0f); // 10
	vertices[41] = Vector3(+0.3f, +0.7f, +0.5f); // Color
	vertices[42] = Vector3(+1.0f, +0.0f, +0.0f); // Normal
	vertices[43] = Vector3(+1.0f, +0.0f, +0.0f); // UV
	vertices[44] = Vector3(+1.0f, -1.0f, -1.0f); // 11
	vertices[45] = Vector3(+0.5f, +0.7f, +0.5f); // Color
	vertices[46] = Vector3(+1.0f, +0.0f, +0.0f); // Normal
	vertices[47] = Vector3(+0.0f, +0.0f, +0.0f); // UV
	
	//Left
	vertices[48] = Vector3(-1.0f, +1.0f, +1.0f); // 12
	vertices[49] = Vector3(+0.7f, +0.8f, +0.2f); // Color
	vertices[50] = Vector3(-1.0f, +0.0f, +0.0f); // Normal
	vertices[51] = Vector3(+0.0f, +1.0f, +0.0f); // UV
	vertices[52] = Vector3(-1.0f, +1.0f, -1.0f); // 13
	vertices[53] = Vector3(+0.5f, +0.7f, +0.3f); // Color
	vertices[54] = Vector3(-1.0f, +0.0f, +0.0f); // Normal
	vertices[55] = Vector3(+1.0f, +1.0f, +0.0f); // UV
	vertices[56] = Vector3(-1.0f, -1.0f, -1.0f); // 14
	vertices[57] = Vector3(+0.4f, +0.7f, +0.7f); // Color
	vertices[58] = Vector3(-1.0f, +0.0f, +0.0f); // Normal
	vertices[59] = Vector3(+1.0f, +0.0f, +0.0f); // UV
	vertices[60] = Vector3(-1.0f, -1.0f, +1.0f); // 15
	vertices[61] = Vector3(+0.2f, +0.5f, +1.0f); // Color
	vertices[62] = Vector3(-1.0f, +0.0f, +0.0f); // Normal
	vertices[63] = Vector3(+0.0f, +0.0f, +0.0f); // UV
	
	//Back
	vertices[64] = Vector3(+1.0f, +1.0f, +1.0f); // 16
	vertices[65] = Vector3(+0.6f, +1.0f, +0.7f); // Color
	vertices[66] = Vector3(+0.0f, +0.0f, -1.0f); // Normal
	vertices[67] = Vector3(+0.0f, +1.0f, +0.0f); // UV
	vertices[68] = Vector3(-1.0f, +1.0f, +1.0f); // 17
	vertices[69] = Vector3(+0.6f, +0.4f, +0.8f); // Color
	vertices[70] = Vector3(+0.0f, +0.0f, -1.0f); // Normal
	vertices[71] = Vector3(+1.0f, +1.0f, +0.0f); // UV
	vertices[72] = Vector3(-1.0f, -1.0f, +1.0f); // 18
	vertices[73] = Vector3(+0.2f, +0.8f, +0.7f); // Color
	vertices[74] = Vector3(+0.0f, +0.0f, -1.0f); // Normal
	vertices[75] = Vector3(+1.0f, +0.0f, +0.0f); // UV
	vertices[76] = Vector3(+1.0f, -1.0f, +1.0f); // 19
	vertices[77] = Vector3(+0.2f, +0.7f, +1.0f); // Color
	vertices[78] = Vector3(+0.0f, +0.0f, -1.0f); // Normal
	vertices[79] = Vector3(+0.0f, +0.0f, +0.0f); // UV
	
	//Bottom
	vertices[80] = Vector3(+1.0f, -1.0f, -1.0f); // 20
	vertices[81] = Vector3(+0.8f, +0.3f, +0.7f); // Color
	vertices[82] = Vector3(+0.0f, -1.0f, +0.0f); // Normal
	vertices[83] = Vector3(+0.0f, +1.0f, +0.0f); // UV
	vertices[84] = Vector3(-1.0f, -1.0f, -1.0f); // 21
	vertices[85] = Vector3(+0.8f, +0.9f, +0.5f); // Color
	vertices[86] = Vector3(+0.0f, -1.0f, +0.0f); // Normal
	vertices[87] = Vector3(+1.0f, +1.0f, +0.0f); // UV
	vertices[88] = Vector3(-1.0f, -1.0f, +1.0f); // 22
	vertices[89] = Vector3(+0.5f, +0.8f, +0.5f); // Color
	vertices[90] = Vector3(+0.0f, -1.0f, +0.0f); // Normal
	vertices[91] = Vector3(+1.0f, +0.0f, +0.0f); // UV
	vertices[92] = Vector3(+1.0f, -1.0f, +1.0f); // 23
	vertices[93] = Vector3(+0.9f, +1.0f, +0.2f); // Color
	vertices[94] = Vector3(+0.0f, -1.0f, +0.0f); // Normal
	vertices[95] = Vector3(+0.0f, +0.0f, +0.0f); // UV
}

void Cube::createCubeIndices()
{
	//Top
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 2;
	indices[3]  = 0;
	indices[4]  = 2;
	indices[5]  = 3;
		
	//Front
	indices[6]  = 4;
	indices[7]  = 5;
	indices[8]  = 6;
	indices[9]  = 4;
	indices[10] = 6;
	indices[11] = 7;
		
	//Right
	indices[12] = 8;
	indices[13] = 9;
	indices[14] = 10;
	indices[15] = 8;
	indices[16] = 10;
	indices[17] = 11;
		
	//Left
	indices[18] = 12;
	indices[19] = 13;
	indices[20] = 14;
	indices[21] = 12;
	indices[22] = 14;
	indices[23] = 15;
		
	//Back
	indices[24] = 16;
	indices[25] = 17;
	indices[26] = 18;
	indices[27] = 16;
	indices[28] = 18;
	indices[29] = 19;
		
	//Bottom
	indices[30] = 20;
	indices[31] = 22;
	indices[32] = 21;
	indices[33] = 20;
	indices[34] = 23;
	indices[35] = 22;
}