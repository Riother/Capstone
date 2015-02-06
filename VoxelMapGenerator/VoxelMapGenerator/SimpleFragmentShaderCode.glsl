#version 400

in vec3 position;
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
	//if(color.x == 0 && color.y == 1 && color.z == 0 && color.w == 1z)
		//theFinalColor = color;
	//else

	if(useImage)
		theFinalColor = texture(image, flippedUV).rgba;// * color;
	else
		theFinalColor = color;

	if(theColor.x  < 0.05 || theColor.z < 0.05)
		theFinalColor = vec4(1, 1, 1, 1);
};