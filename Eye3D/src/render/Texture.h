#pragma once

#include "../common.h"
namespace UxDeepEye {
	class CTexture {
	public:
		CTexture(const char *path);
		~CTexture();

		GLuint GetTexture();
	private:
		GLuint _textureID;
		std::string _texturePath;
		bool _isReady;
	};
}