#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec4 color;

uniform mat4 transformation;

out vec4 theColor;
out vec3 thePosition;

void main()
{
	gl_Position = transformation * vec4(position, 1);

	theColor = color;
}