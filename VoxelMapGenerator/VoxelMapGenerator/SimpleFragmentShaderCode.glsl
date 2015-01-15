#version 400

in vec4 theColor;

uniform vec4 color;
out vec4 theFinalColor;

void main()
{
	theFinalColor = theColor;
};