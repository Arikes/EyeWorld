#ifndef H_BETAIMAGE_H
#define H_BETAIMAGE_H
#include "../../common.h"
#include "../Texture.h"
#include "../UxFrameBuffer.h"

namespace UxDeepEye {
	static const char *vsh5 = ""
		"attribute vec4 position;\n"
		"attribute vec2 texcoord;\n"
		"varying vec2 coord;\n"
		"void main()\n"
		"{\n"
		"   coord = texcoord;\n"
		"	vec4 pos = position;\n"
		"	gl_Position = pos;\n"
		"}\n";
	static const char *fsh5 = ""
		"uniform sampler2D texture;\n"
		"varying vec2 coord;\n"
		"void main()\n"
		"{\n"
		"vec4 color = texture2D(texture,coord);\n"
		"gl_FragColor = vec4(color.rgb,1.0);\n"
		"}\n"
		"";

	class CBetaImage {
	public:
		CBetaImage();
		virtual ~CBetaImage();

		GLuint DrawFrame();

	private:
		void CfgShader();

	private:
		GLuint _programHandle;
		GLuint _positionHandle;
		GLuint _texcoordHandle;

		GLuint _textureHandle;
		CTexture *_texture;


		bool _shaderReady;

		UxFrameBuffer *m_framebuf;
	};
}

#endif