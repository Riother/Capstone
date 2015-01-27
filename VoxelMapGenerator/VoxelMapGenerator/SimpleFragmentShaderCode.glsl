#version 400

in vec4 theColor;
in vec3 theNormal;
in vec2 theUV;

uniform vec4 color;
uniform bool useImage;
uniform sampler2D image;

out vec4 theFinalColor;

void main()
{
	vec2 flippedUV = vec2(theUV.x, 1 - theUV.y);
	//if(color.x == 0 && color.y == 1 && color.z == 0 && color.w == 1)
		//theFinalColor = color;
	//else
		theFinalColor = texture(image, flippedUV).rgba;
};