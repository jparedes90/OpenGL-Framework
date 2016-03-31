#version 400

//////////////////////////
//Input Variables
//////////////////////////
layout(location = 0)in vec3 vertex_modelSpace;
layout(location = 1)in vec2 texture_coordinates;

out vec2 texCoord;

//////////////////////////
//Uniform Variables
//////////////////////////
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//////////////////////////
//Vertex Shader
//////////////////////////
void main(void)
{
	mat4 mvp = worldMatrix * viewMatrix * projectionMatrix;
	gl_Position = mvp * vec4(vertex_modelSpace, 1.0);

	texCoord = texture_coordinates;
}