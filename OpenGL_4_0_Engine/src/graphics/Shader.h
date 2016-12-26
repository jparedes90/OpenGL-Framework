#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#include "OGL.h"
#include "../maths/MathCore.h"

class TextureLoader;

class Shader
{
public:
	Shader();
	~Shader();

	bool Initialize(string shaderFileName);
	void BindAttributes(int index, const char* name);
	void BeginShader();
	void EndShader();

	bool SetShaderMatrixParameter(const char* name, float* matrix);
	bool SetShaderFloatParameter(const char* name, float pValue);
	bool SetShaderIntParameter(const char* name, int pValue);
	bool SetShaderVec2Parameter(const char* name, Vector2 vec2);
	bool SetShaderVec3Parameter(const char* name, Vector3 vec3);
	bool SetShaderSampler(const char* name, int slot, TextureLoader* texture);

	GLuint GetAttribute(const string& name);
	unsigned int GetProgramID() { return m_programID; }

	void OutputShaderErrorMessage(unsigned int shaderID, char* shaderFilename);
	void OutputLinkerErrorMessage(unsigned int programID);

private:
	bool InitializeShader(string shaderVSFileName, string shaderPSFileName);
	char* LoadShaderSourceFile(string shaderFileName);
	void DeleteProgram();

	unsigned int m_programID;
	unsigned int m_vertexID;
	unsigned int m_fragID;
	string m_name;
};

#endif
