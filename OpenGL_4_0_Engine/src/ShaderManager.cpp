//Date: 5/14/13
#include "ShaderManager.h"

ShaderManager* ShaderManager::m_instance = NULL;
map<string, Shader*> ShaderManager::m_shaders;

ShaderManager::ShaderManager()
{
	m_instance = this;
}

ShaderManager::~ShaderManager()
{
	if(!m_shaders.empty())
	{
		map<string, Shader*>::iterator it = m_shaders.begin();

		for(; it != m_shaders.end(); ++it)
		{
			Shader* shader = (*it).second;
			delete shader;
			shader = NULL;
		}
		m_shaders.clear();
	}
}

void ShaderManager::AddShader(const char* shaderFileName, string type)
{
	if(m_shaders.find(type) != m_shaders.end()) return;

	m_shaders[type] = new Shader();
	m_shaders[type]->Initialize(shaderFileName);
}

Shader* ShaderManager::GetShader(string pType)
{
	if(m_shaders.empty() || m_shaders.find(pType) == m_shaders.end())
	{
		return NULL;
	}
	return m_shaders[pType];
}

ShaderManager* ShaderManager::GetInstance()
{
	return m_instance;
}