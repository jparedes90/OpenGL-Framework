//Date: 5/14/13
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <map>
#include "../graphics/Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();
	enum ShaderType
	{
		VERTEX,
		COUNT,
	};

	static ShaderManager* GetInstance();
	void AddShader(const char* shaderFileName, string name);
	static Shader* GetShader(string pType);
private:

	static ShaderManager* m_instance;
	static map<string, Shader*> m_shaders;
};

#endif
