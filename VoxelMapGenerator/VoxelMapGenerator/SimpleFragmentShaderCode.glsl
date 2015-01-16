#version 400

in vec4 theColor;

uniform vec4 color;
out vec4 theFinalColor;

void main()
{
	if(color.x == 0 && color.y == 1 && color.z == 0 && color.w == 1)
		theFinalColor = color;
	else
		theFinalColor = theColor;
};