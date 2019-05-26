#pragma once
#include "../common.h"
#include "Texture.h"
namespace UxDeepEye {

	static const char *vsh = ""
		"attribute vec4 position;\n"
		"attribute vec2 texcoord;\n"
		"varying vec2 coord;\n"
		"void main()\n"
		"{\n"
		"   coord = texcoord;\n"
		"	vec4 pos = position;\n"
		"	gl_Position = pos;\n"
		"}\n";
	static const char *fsh = ""
		"uniform sampler2D texture;\n"
		"varying vec2 coord;\n"
		"void main()\n"
		"{\n"
		"vec4 color = texture2D(texture,coord);\n"
		"gl_FragColor = color;\n"
		"}\n"
		"";

	class CTestImage {
	public:
		CTestImage();
		virtual ~CTestImage();

		void DrawFrame(GLuint textureID);

	private:
		void CfgShader();

	private:
		GLuint _programHandle;
		GLuint _positionHandle;
		GLuint _texcoordHandle;

		GLuint _textureHandle;
		CTexture *_texture;


		bool _shaderReady;
	};
}