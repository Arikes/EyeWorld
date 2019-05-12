#pragma once
#include "../common.h"
#include "Texture.h"
namespace UxDeepEye {

	static const char *vsh2 = ""
		"attribute vec4 position;\n"
		"attribute vec2 texcoord;\n"
		"varying vec2 coord;\n"
		"void main()\n"
		"{\n"
		"   coord = texcoord;\n"
		"	vec4 pos = position;\n"
		"	gl_Position = pos;\n"
		"}\n";
	static const char *fsh2 = ""
		"uniform sampler2D texture;\n"
		"varying vec2 coord;\n"
		"void main()\n"
		"{\n"
		"vec4 color = texture2D(texture,coord);\n"
		"color.r = 0.0;\n"
		"color.g = 0.0;\n"
		"color.b = 1.0;\n"
		"gl_FragColor = color;\n"
		"}\n"
		"";

	class CTestFont {
	public:
		CTestFont();
		virtual ~CTestFont();

		void DrawFrame();

	private:
		void CfgShader();

	private:
		GLuint _programHandle;
		GLuint _positionHandle;
		GLuint _texcoordHandle;

		GLuint _textureHandle;
		CTexture *_texture;

		GLuint _textureFont;

		bool _shaderReady;
	};
}