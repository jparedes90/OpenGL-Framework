#version 400

/////////////////////////
//Output Variables
/////////////////////////
out vec4 outputColor;

in vec2 texCoord;

/////////////////////////
//Pixel Shader
/////////////////////////
void main(void)
{
	if (texCoord.x > 0.25 && texCoord.x < 0.75 &&
		texCoord.y > 0.25 && texCoord.y < 0.75)
	{
		outputColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		outputColor = vec4(1.0);
	}
}