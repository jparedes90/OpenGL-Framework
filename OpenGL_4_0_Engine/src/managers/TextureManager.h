//#pragma once
#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H
#include "../graphics/TextureLoader.h"

#include <vector>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static TextureManager* GetInstance();

	//Function: Adds a texture to the list
	//PostCondition: Texture is added
	void AddTexture(char* filePath, char* extension, char* pName);
	void AddTexture(TextureLoader* texture);
	//Function: finds texture by name
	//PostCondition: texture returned if found
	static TextureLoader* GetTexture(const char* name);

	void SetRootDirectory(const char* pRootDirectory);

private:
	static TextureManager* m_instance;
	static std::vector<TextureLoader*> m_textures;
	char* m_rootDirectory;
};
#endif
