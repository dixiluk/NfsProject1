#include "Texture.h"

Texture::Texture(const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	glGenTextures(1, &this->id);

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(0);
	BYTE* bits(0);
	unsigned int width(0), height(0);
	GLuint gl_texID;

	fif = FreeImage_GetFileType(filename, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	if (fif == FIF_UNKNOWN){
		ReportWarning("Texture file format undefined");
		return;
	}


	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);

	if (!dib)
		ReportWarning("Could not load texture");

	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	//if((bits == 0) || (width == 0) || (height == 0))
	//ReportWarning("Wrong bits");
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);


	FreeImage_Unload(dib);
}

Texture::~Texture()
{

}

void Texture::bind()
{
	printf("%d", this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);
}

GLuint Texture::getId()
{
	return id;
}
