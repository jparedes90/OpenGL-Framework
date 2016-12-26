#include <assert.h>
#include "../managers/TextureManager.h"
#include "Common.h"
#include "debug/Logger.h"
#include "png.h"
#include "zlib.h"

extern "C" {
  #include "jpeglib.h" 
} 

using namespace std;

TextureLoader::TextureLoader()
{
	m_textureTarget = GL_TEXTURE_2D;
	m_pixels = NULL;
	m_width = m_height = 0;
	m_texHandle = GL_ZERO;
	m_textureType = NONE;
	m_bytesPerPixel = 0;
	m_name = "";
}

TextureLoader::TextureLoader(const char* fileName, const char* extension)
{
	m_textureTarget = GL_TEXTURE_2D;
	m_pixels = NULL;
	m_width = m_height = 0;
	m_texHandle = NULL;
	m_textureType = NONE;
	m_bytesPerPixel = 0;
	m_name = "";

	bool read = Read(fileName, extension);
	assert(read);
	(void)read;
}

TextureLoader::~TextureLoader()
{
	if(m_pixels)
	{
		delete [] m_pixels;
		m_pixels = NULL;
	}
}

void TextureLoader::Bind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_textureTarget, m_texHandle);
}

void TextureLoader::UnBind()
{
	glBindTexture(m_textureTarget, 0);
}

bool TextureLoader::Read(const char* fileName, const char* extension)
{
	char result[256];
	char* mssg = NULL;
	char* mesh = (char*)fileName;
	char* end = " Texture";

	m_name = string(fileName);

	if(!strcmp(extension, ".png"))
	{
		m_textureType = PNG;

		if(!ReadPng(fileName))
		{
			return false;
		}

		glVerifyState();
	}
	else if(!strcmp(extension, ".jpg"))
	{
		m_textureType = JPG;

		if(!ReadJpeg(fileName))
		{
			return false;
		}

		glVerifyState();
	}

	mssg = "Successfully Loaded ";

	strcpy_s(result, mssg);
	strcat_s(result, mesh);
	strcat_s(result, end);

	int len = (int)strlen(mssg) + (int)strlen(mesh) + (int)strlen(end);

	result[len] = '\0';

	Log::Trace(string(result));

	return true;
}

bool TextureLoader::ReadPng(const char* fileName)
{
	png_byte header[8];

	FILE *fp;
	if(fopen_s(&fp, fileName, "rb") != 0)
	{
		perror(fileName);
		return false;
	}

	fread(header, 1, 8, fp);

	if(png_sig_cmp(header, 0, 8))
	{
		Log::Error(string(fileName) + " is not a PNG");
		fclose(fp);
		return false;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
	{
		Log::Error("could not png_create_read_struct from file: " + string(fileName));
		fclose(fp);
		return false;
	}

	// create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
	Log::Error("could not png_create_info_struct from file: " + string(fileName));

		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	png_infop end_info = png_create_info_struct(png_ptr);
	if(!end_info)
	{
		Log::Error("could not png_create_info_struct from file: " + string(fileName));

		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		return false;
	}

	//// the code in this if statement gets called if libpng encounters an error
	//if (setjmp(png_jmpbuf(png_ptr)))
	//{
	//	cout << "Error on libpng end" << endl;
	//	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
 //       fclose(fp);
	//	return false;
	//}

	//init png reading
	png_init_io(png_ptr, fp);

	//let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	//read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	//variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 temp_width, temp_height, channels;

	//get infro about png
	png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type, NULL, NULL, NULL);

	channels = png_get_channels(png_ptr, info_ptr);
	switch (color_type) {
        case PNG_COLOR_TYPE_PALETTE:
           // png_set_palette_to_rgb(pngPtr);
            //Don't forget to update the channel info (thanks Tom!)
            //It's used later to know how big a buffer we need for the image
            channels = 3;           
            break;
        case PNG_COLOR_TYPE_GRAY:
            //if (bitdepth < 8)
            //png_set_expand_gray_1_2_4_to_8(pngPtr);
            //And the bitdepth info
            //bitdepth = 8;
            break;
    }

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
        channels+=1;
    }

	m_bytesPerPixel = channels;

	m_width = temp_width;
	m_height = temp_height;

	//update the png info struct
	png_read_update_info(png_ptr, info_ptr);

	//row size in bytes
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	// glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block, to be given to opengl
	m_pixels = new U8[rowbytes * m_height * sizeof(U8) + 15];
	if(m_pixels == NULL)
	{
		Log::Error("could not allocate memory for PNG Image data: " + string(fileName));

		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
		return false;
	}
	
	/*if (setjmp(png_jmpbuf(png_ptr)))
	{}*/

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep* row_pointers = (png_bytep*)malloc(m_height * sizeof(png_bytep));
	if(row_pointers == NULL)
	{
		Log::Error("could not allocate memory for PNG Image pointers: " + string(fileName));

		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		delete [] m_pixels;
		m_pixels = NULL;
        fclose(fp);
		return false;
	}

	const unsigned int stride = temp_width * bit_depth * channels / 8;

	U32 i;
	for(i = 0; i < m_height; ++i)
	{
		png_uint_32 q = (m_height- i - 1) * stride;
		row_pointers[i] = (U8*)m_pixels + q;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	GLint internalFormat = (channels == 3) ? GL_RGB : GL_RGBA;
	GLenum formatEnum = (channels == 3) ? GL_RGB : GL_RGBA;
	
	glGenTextures(1, &m_texHandle);
    glBindTexture(GL_TEXTURE_2D, m_texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, temp_width, temp_height, 0, formatEnum, GL_UNSIGNED_BYTE, m_pixels);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	// clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(row_pointers);
    fclose(fp);

	return true;
}

bool TextureLoader::ReadJpeg(const char* fileName)
{
	unsigned long data_size;     // length of the file
	int channels;               //  3 =>RGB   4 =>RGBA  
	unsigned char * rowptr[1];    // pointer to an array
	struct jpeg_decompress_struct info; //for our jpeg info
	struct jpeg_error_mgr err;          //the error handler
	
	FILE* file;  //open the file
	if(fopen_s(&file, fileName, "rb") != 0)
	{
		Log::Error("Couldnt open " + string(fileName));

		perror(fileName);
		return false;
	}
	
	info.err = jpeg_std_error(& err);     
	jpeg_create_decompress(& info);   //fills info structure
	
	//if the jpeg file doesn't load
	if(!file) 
	{
	   Log::Error("Error reading JPEG file " + string(fileName));

	   return false;
	}
	
	jpeg_stdio_src(&info, file);    
	jpeg_read_header(&info, TRUE);   // read jpeg file header
	
	jpeg_start_decompress(&info);    // decompress the file
	
	//set width and height
	m_width = info.output_width;
	m_height = info.output_height;
	channels = info.num_components;

	GLint internalFormat = (channels == 3) ? GL_RGB : GL_RGBA;
	GLenum formatEnum = (channels == 3) ? GL_RGB : GL_RGBA;

	m_bytesPerPixel = channels;
	
	data_size = m_width * m_height * m_bytesPerPixel;
	
	//--------------------------------------------
	// read scanlines one at a time & put bytes 
	//    in jdata[] array. Assumes an RGB image
	//--------------------------------------------
	m_pixels = (U8*)malloc(data_size);
	while (info.output_scanline < info.output_height) // loop
	{
	  // Enable jpeg_read_scanlines() to fill our jdata array
	  rowptr[0] = (U8*)m_pixels +  // secret to method
	          3* info.output_width * info.output_scanline; 
	
	  jpeg_read_scanlines(&info, rowptr, 1);
	}
	//---------------------------------------------------
	
	jpeg_finish_decompress(&info);   //finish decompressing
	
	//----- create OpenGL tex map (omit if not needed) --------
	glGenTextures(1, &m_texHandle);
	glBindTexture(GL_TEXTURE_2D, m_texHandle);
	//gluBuild2DMipmaps(GL_TEXTURE_2D,3,m_width,m_height,GL_RGB,GL_UNSIGNED_BYTE,jdata);

	//glGenTextures(1, &m_texHandle);
	//glBindTexture(GL_TEXTURE_2D, m_texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, formatEnum, GL_UNSIGNED_BYTE, m_pixels);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	fclose(file);                    //close the file

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

U32 TextureLoader::GetWidth()const
{
	return m_width;
}

U32 TextureLoader::GetHeight()const
{
	return m_height;
}

U32 TextureLoader::GetBytesPerPixel()const
{
	return m_bytesPerPixel;
}

const U8* TextureLoader::GetBuffer()const
{
	return (U8*)m_pixels;
}

void TextureLoader::SetName(const string& name)
{
	m_name = name;
}

string TextureLoader::GetName()
{
	return m_name;
}
