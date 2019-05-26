#include "BetaImage.h"
#include "../../util/RenderUtil.h"
namespace UxDeepEye {
	CBetaImage::CBetaImage() :_shaderReady(false), m_framebuf(nullptr){
	}

	CBetaImage::~CBetaImage() {
	}

	GLuint CBetaImage::DrawFrame() {
		if (!_shaderReady) {
			if (!m_framebuf) {
				m_framebuf = new UxFrameBuffer(800, 600);
			}
			_programHandle = CRenderUtil::loadProgram(vsh5, fsh5);
			CfgShader();
			_texture = new CTexture("d:/hide/1-1F62G14035.jpg");
			_shaderReady = true;
		}

		glUseProgram(_programHandle);
		GLfloat verts[] = {
			-1.0,-1.0,0.0,
			1.0,-1.0,0.0,
			-1.0,1.0,0.0,
			1.0,1.0,0.0
		};

		GLfloat texcoords[] = {
			0.0,1.0,
			1.0,1.0,
			0.0,0.0,
			1.0,0.0
		};

		GLubyte indices[] = {
			0,1,2,
			1,3,2
		};
		glEnableVertexAttribArray(_positionHandle);
		glEnableVertexAttribArray(_texcoordHandle);

		glVertexAttribPointer(_positionHandle, 3, GL_FLOAT, GL_FALSE, 0, verts);
		glEnableVertexAttribArray(_positionHandle);

		glVertexAttribPointer(_texcoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texcoords);
		glEnableVertexAttribArray(_texcoordHandle);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture->GetTexture());
		glUniform1i(_texcoordHandle, 0);

		m_framebuf->bindFrameBuf();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_BYTE, indices);
		m_framebuf->unBindFrameBuf();
		std::cout << "CTestImage DrawFrame" << std::endl;
		return m_framebuf->getTexID();
	}

	void CBetaImage::CfgShader() {
		glUseProgram(_programHandle);
		_positionHandle = glGetAttribLocation(_programHandle, "position");
		_texcoordHandle = glGetAttribLocation(_programHandle, "texcoord");
		_textureHandle = glGetUniformLocation(_programHandle, "texture");
	}
}