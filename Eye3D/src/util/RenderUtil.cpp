#include "RenderUtil.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace UxDeepEye {
	GLuint CRenderUtil::loadProgram(const char *vsh, const char *fsh) {
		GLuint vertShader = compileShader(GL_VERTEX_SHADER, vsh);
		GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fsh);

		GLuint programHandle = glCreateProgram();
		glAttachShader(programHandle, vertShader);
		glAttachShader(programHandle, fragShader);

		GLint status = 0;
		glLinkProgram(programHandle);
		glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			char compileLog[1024] = {0};
			glGetProgramInfoLog(programHandle, sizeof(compileLog), 0, compileLog);
			return 0;
		}

		return programHandle;
	}

	GLuint CRenderUtil::compileShader(GLenum type, const char *shader) {
		GLuint shaderHandle = glCreateShader(type);
		glShaderSource(shaderHandle, 1, &shader, 0);
		glCompileShader(shaderHandle);

		GLint status = 0;
		char compileLog[1024] = { 0 };
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			glGetShaderInfoLog(shaderHandle, sizeof(compileLog), 0, compileLog);
			shaderHandle = 0;
			return 0;
		}
		return shaderHandle;
	}

	 GLuint CRenderUtil::loadTexture(const char *texturePath) {
		GLuint _textureId;
		//1 获取图片格式
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texturePath, 0);

		//2 加载图片
		FIBITMAP *dib = FreeImage_Load(fifmt, texturePath, 0);
		//3 转化为rgb 24色
		dib = FreeImage_ConvertTo24Bits(dib);

		//4 获取数据指针
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);

		/**
		* 产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
		*/
		glGenTextures(1, &_textureId);

		/**
		* 使用这个纹理id,或者叫绑定(关联)
		*/
		glBindTexture(GL_TEXTURE_2D, _textureId);
		/**
		* 指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/**
		* 将图片的rgb数据上传给opengl.
		*/
		glTexImage2D(
			GL_TEXTURE_2D, //! 指定是二维图片
			0, //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
			GL_RGB, //! 纹理的使用的存储格式
			width, //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
			height, //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
			0, //! 是否的边
			GL_BGR_EXT, //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
			GL_UNSIGNED_BYTE, //! 数据是8bit数据
			pixels
		);
		/**
		* 释放内存
		*/
		FreeImage_Unload(dib);

		return _textureId;
	}

	 GLuint CRenderUtil::TextureFromFile(const char *path, const std::string &directory, bool gamma) {
		 std::string filename = std::string(path);
		 filename = directory + '/' + filename;

		 unsigned int textureID;
		 glGenTextures(1, &textureID);

		 int width, height, nrComponents;
		 unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		 if (data)
		 {
			 GLenum format;
			 if (nrComponents == 1)
				 format = GL_RED;
			 else if (nrComponents == 3)
				 format = GL_RGB;
			 else if (nrComponents == 4)
				 format = GL_RGBA;

			 glBindTexture(GL_TEXTURE_2D, textureID);
			 glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			 glGenerateMipmap(GL_TEXTURE_2D);

			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			 stbi_image_free(data);
		 }
		 else
		 {
			 std::cout << "Texture failed to load at path: " << path << std::endl;
			 stbi_image_free(data);
		 }

		 return textureID;
	 }
}