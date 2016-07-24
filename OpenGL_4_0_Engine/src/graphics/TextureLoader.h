#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <GL\glew.h>
#include <string>

typedef unsigned int U32;
typedef unsigned char U8;

class TextureLoader
{
public:
	enum TextureType
	{
		NONE,
		PNG,
		JPG,
	};

	TextureLoader();
	TextureLoader(const char* fileName, const char* extension);
	~TextureLoader();

	bool Read(const char* fileName, const char* extension);

	U32 GetWidth()const;
	U32 GetHeight()const;
	U32 GetBytesPerPixel()const;

	void Bind(int slot = 0);
	void UnBind();

	U32 GetHandle() { return m_texHandle; }

	void SetName(const std::string& name);
	std::string GetName();

	const U8* GetBuffer()const;

	TextureType GetTextureType() { return m_textureType; }

private:

	bool ReadPng(const char* fileName);
	bool ReadJpeg(const char* fileName);

	TextureType m_textureType;
	GLenum m_textureTarget;
	U8* m_pixels;
	U32 m_width;
	U32 m_height;
	U32 m_bytesPerPixel;
	U32 m_texHandle;
	std::string m_name;
};

#endif
