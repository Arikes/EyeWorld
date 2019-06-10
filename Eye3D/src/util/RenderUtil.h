#pragma once
#include "../common.h"
namespace UxDeepEye {
	class CRenderUtil {
	public:
		static GLuint loadProgram(const char *vsh, const char *fsh);

		static GLuint compileShader(GLenum type, const char *shader);

		static GLuint loadTexture(const char *texturePath);

		static GLuint TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
	};
};