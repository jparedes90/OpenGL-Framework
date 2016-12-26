#include "Shader.h"
#include "../app/Engine.h"
#include <assert.h>
#include <stdio.h>

Shader::Shader()
{
}

Shader::~Shader()
{
	DeleteProgram();
}

bool Shader::Initialize(string shaderFileName)
{
	m_name = shaderFileName;

	string vsFile = shaderFileName + "_vs.glsl";
	string psFile = shaderFileName + "_ps.glsl";

	if (!InitializeShader(vsFile, psFile))
	{
		cout << "Shader " << shaderFileName << " couldnt be initialized" << endl;
		return false;
	}

	return true;
}

void Shader::BeginShader()
{
	glUseProgram(m_programID);
}

void Shader::EndShader()
{
	glUseProgram(NULL);
}

bool Shader::InitializeShader(string shaderVSFileName, string shaderPSFileName)
{
	const char* shaderBuffer_VS = LoadShaderSourceFile("Shaders/" + shaderVSFileName);
	const char* shaderBuffer_PS = LoadShaderSourceFile("Shaders/" + shaderPSFileName);

	if (!shaderBuffer_VS)
	{
		cout << "Shader: " << shaderVSFileName << " could not be loaded" << endl;
		return false;
	}

	if (!shaderBuffer_PS)
	{
		cout << "Shader: " << shaderVSFileName << " could not be loaded" << endl;
		return false;
	}

	m_vertexID = glCreateShader(GL_VERTEX_SHADER);
	m_fragID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexID, 1, &shaderBuffer_VS, NULL);
	glShaderSource(m_fragID, 1, &shaderBuffer_PS, NULL);

	delete[] shaderBuffer_VS;
	delete[] shaderBuffer_PS;

	glCompileShader(m_vertexID);
	glCompileShader(m_fragID);
	
	int status;

	glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &status);

	if (status != 1)
	{
		OutputShaderErrorMessage(m_vertexID, (char*)shaderVSFileName.c_str());
		return false;
	}

	glGetShaderiv(m_fragID, GL_COMPILE_STATUS, &status);

	if (status != 1)
	{
		OutputShaderErrorMessage(m_fragID, (char*)shaderPSFileName.c_str());
		return false;
	}

	m_programID = glCreateProgram();//set the Program ID to the first element by default

	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragID);

	glLinkProgram(m_programID);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &status);

	if(status != 1)
	{
		// If it did not link then write the syntax error message out to a text file for review.
		OutputLinkerErrorMessage(m_programID);

		DeleteProgram();

		return false;
	}

	return true;
}

void Shader::BindAttributes(int index, const char* name)
{
	assert(m_programID);
	glBindAttribLocation(m_programID, index, name);
}

char* Shader::LoadShaderSourceFile(string shaderFileName)
{
	FILE *pFile = NULL;
	char* shaderBuffer = NULL;

	fopen_s(&pFile, shaderFileName.c_str(), "rb");
	if(!pFile)
	{
		return NULL;
	}

	//get size of the file
	fseek(pFile, 0L, SEEK_END);
	//file lenght
	unsigned int bufferSize = ftell(pFile);
	//back to the start of the file
	rewind(pFile);

	shaderBuffer = new char[bufferSize+1];
	if(fread(shaderBuffer, bufferSize, 1, pFile) <= 0)
	{
		delete [] shaderBuffer;
		fclose(pFile);
		return NULL;
	}
	shaderBuffer[bufferSize] = '\0';
	fclose(pFile);

	return shaderBuffer;
}

void Shader::OutputShaderErrorMessage(unsigned int shaderID, char* shaderFilename)
{
	int logSize;
	char* infoLog;
	ofstream fout;

	//get the size of the string containing the info log
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
	
	if(!logSize)
	{
		return;
	}

	infoLog = new char[logSize + 1];

	//retrieve info log
	glGetShaderInfoLog(shaderID, logSize, NULL, infoLog);

	//open a file to write to
	fout.open("shader-error.txt");

	for(int i = 0; i < logSize+1; ++i)
	{
		fout << infoLog[i];
	}

	fout.close();

	delete [] infoLog;

	//pop message on screen
	MessageBox(Engine::GetEngine()->GetGraphics()->GetOpenGL()->GetHWND(), "Error compiling shader. Check shader-error.txt for message", shaderFilename, MB_OK);
}

void Shader::OutputLinkerErrorMessage(unsigned int programID)
{
	int logSize;
	char* infoLog;
	ofstream fout;

	//get the size of the string containing the info log
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);
	
	if(!logSize)
	{
		return;
	}

	infoLog = new char[logSize + 1];

	//retrieve info log
	glGetProgramInfoLog(programID, logSize, NULL, infoLog);

	//open a file to write to
	fout.open("shader-linkerror.txt");

	for(int i = 0; i < logSize+1; ++i)
	{
		fout << infoLog[i];
	}

	fout.close();

	delete [] infoLog;

	//pop message on screen
	MessageBox(Engine::GetEngine()->GetGraphics()->GetOpenGL()->GetHWND(), "Error compiling shader. Check shader-error.txt for message", "LinkerError", MB_OK);
}

bool Shader::SetShaderMatrixParameter(const char* name, float* matrix)
{
	int locID = glGetUniformLocation(m_programID, name);

	if (locID >= 0)
	{
		glUniformMatrix4fv(locID, 1, true, matrix);
	}

	return true;
}

bool Shader::SetShaderFloatParameter(const char* name, float pValue)
{
	int locID = glGetUniformLocation(m_programID, name);

	if (locID >= 0)
	{
		glUniform1f(locID, pValue);
	}
	return true;
}

bool Shader::SetShaderIntParameter(const char* name, int pValue)
{
	int locID = glGetUniformLocation(m_programID, name);

	if (locID >= 0)
	{
		glUniform1i(locID, pValue);
	}
	return true;
}

bool Shader::SetShaderVec2Parameter(const char* name, Vector2 vec2)
{
	int locID = glGetUniformLocation(m_programID, name);

	if (locID >= 0)
	{
		glUniform2f(locID, vec2.GetX(), vec2.GetY());
	}
	return true;
}

bool Shader::SetShaderVec3Parameter(const char* name, Vector3 vec3)
{
	int locID = glGetUniformLocation(m_programID, name);

	if (locID >= 0)
	{
		glUniform3f(locID, vec3.GetX(), vec3.GetY(), vec3.GetZ());
	}
	return true;
}

bool Shader::SetShaderSampler(const char* name, int slot, TextureLoader* texture)
{
	if(texture == NULL)
	{
		cout << "Shader::SetShaderSampler setting a null texture" << endl;
		return true;
	}

	int locID = glGetUniformLocation(m_programID, name);

	if (locID >= 0)
	{
		texture->Bind(slot);
		glUniform1i(locID, slot);
	}

	return true;
}

void Shader::DeleteProgram()
{
	glDetachShader(m_programID, m_vertexID);
	glDeleteShader(m_vertexID);
	glDetachShader(m_programID, m_fragID);
	glDeleteShader(m_fragID);

	glDeleteProgram(m_programID);
}
