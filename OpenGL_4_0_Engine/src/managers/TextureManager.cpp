#include "TextureManager.h"
#include "debug/Logger.h"

using namespace std;

TextureManager* TextureManager::m_instance = NULL;
vector<TextureLoader*> TextureManager::m_textures;

TextureManager::TextureManager()
{
	m_instance = this;
	m_rootDirectory = NULL;
}

TextureManager::~TextureManager()
{
	while(!m_textures.empty())
	{
		delete m_textures[0];
		m_textures.erase(m_textures.begin());
	}
	m_textures.clear();

	if(m_rootDirectory)
	{
		delete [] m_rootDirectory;
		m_rootDirectory = NULL;
	}
}

//Function: Adds a texture to the list
//PostCondition: Texture is added
void TextureManager::AddTexture(char* filePath, char* extension, char* pName)
{
	char result[256];

	char* end = extension;
	strcpy_s(result, m_rootDirectory);
	strcat_s(result, filePath);
	strcat_s(result, end);

	int rootLen = (int)strlen(m_rootDirectory);
	int len = (int)strlen(filePath);
	int endLen = (int)strlen(end);

	result[rootLen + len + endLen] = '\0';
	
	TextureLoader* texture = new TextureLoader();

	if(!texture->Read(result, extension))
	{
		delete texture;

		Log::Error("Texture: " + string(result) + " couldnt be loaded");
		return;
	}

	texture->SetName(string(pName));

	m_textures.push_back(texture);
}

void TextureManager::AddTexture(TextureLoader* texture)
{
	if (texture == NULL) return;

	m_textures.push_back(texture);
}

//Function: finds texture by name
//PostCondition: texture returned if found
TextureLoader* TextureManager::GetTexture(const char* name)
{
	for(vector<TextureLoader*>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		if(strcmp(name, (*it)->GetName().c_str()))
			continue;

		return (*it);
	}

	Log::Error("ERROR: texture " + string(name) + " not found");

	return NULL;
}

void TextureManager::SetRootDirectory(const char* pRootDirectory)
{
	if(pRootDirectory == NULL) return;

	m_rootDirectory = new char[strlen(pRootDirectory) + 1];
	memcpy(m_rootDirectory, pRootDirectory, strlen(pRootDirectory) + 1);
}

TextureManager* TextureManager::GetInstance()
{
	return m_instance;
}
