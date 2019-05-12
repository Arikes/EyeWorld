#include "Texture.h"
#include "../util/RenderUtil.h"
namespace UxDeepEye {

	CTexture::CTexture(const char *path) :_isReady(false) {
		_texturePath = path;
	}

	CTexture::~CTexture() {
		if (_isReady) {
			glDeleteTextures(1, &_textureID);
			_isReady = false;
		}
	}

	GLuint CTexture::GetTexture() {
		if (!_isReady) {
			_textureID = CRenderUtil::loadTexture(_texturePath.c_str());
			_isReady = true;
		}
		return _textureID;
	}

}