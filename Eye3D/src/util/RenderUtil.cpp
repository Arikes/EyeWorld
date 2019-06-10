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
		//1 ��ȡͼƬ��ʽ
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texturePath, 0);

		//2 ����ͼƬ
		FIBITMAP *dib = FreeImage_Load(fifmt, texturePath, 0);
		//3 ת��Ϊrgb 24ɫ
		dib = FreeImage_ConvertTo24Bits(dib);

		//4 ��ȡ����ָ��
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);

		/**
		* ����һ������Id,������Ϊ��������������Ĳ����������������id
		*/
		glGenTextures(1, &_textureId);

		/**
		* ʹ���������id,���߽а�(����)
		*/
		glBindTexture(GL_TEXTURE_2D, _textureId);
		/**
		* ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/**
		* ��ͼƬ��rgb�����ϴ���opengl.
		*/
		glTexImage2D(
			GL_TEXTURE_2D, //! ָ���Ƕ�άͼƬ
			0, //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
			GL_RGB, //! �����ʹ�õĴ洢��ʽ
			width, //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
			height, //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
			0, //! �Ƿ�ı�
			GL_BGR_EXT, //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
			GL_UNSIGNED_BYTE, //! ������8bit����
			pixels
		);
		/**
		* �ͷ��ڴ�
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