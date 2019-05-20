#pragma once
#include "../common.h"
#include "../util/RenderUtil.h"
#include "Texture.h"
namespace UxDeepEye {

	static const char *vsh3 = ""
		"attribute vec4 position;\n"
		"void main()\n"
		"{\n"
		"	vec4 pos = position;\n"
		"   gl_PointSize = 32.0;\n"
		"	gl_Position = pos;\n"
		"}\n";
	static const char *fsh3 = ""
		"void main()\n"
		"{\n"
		"vec4 color = vec4(1.0,0.0,0.0,1.0);\n"
		"gl_FragColor = color;\n"
		"}\n"
		"";

	class UxBetaParticle {
	public:
		UxBetaParticle();
		~UxBetaParticle();

		void DrawFrame();

	private:
		void CfgShader();
	private:
		bool m_ready;
		GLuint _programHandle;
		GLuint _positionHandle;
	};
}