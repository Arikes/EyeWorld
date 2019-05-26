#include "BaseImageProcessor.h"
namespace UxDeepEye {
	const char* vshPath = "D:/Engine/EyeWorld/Eye3D/Resources/shaders/gaussBlurFilter_v.glsl";
	const char* fshPath = "D:/Engine/EyeWorld/Eye3D/Resources/shaders/gaussBlurFilter_f.glsl";
	CBaseImageProcessor::CBaseImageProcessor(const char* vsh, const char* fsh) :m_vshString(vsh),m_fshString(fsh), m_isReady(false), m_frameBuf(nullptr){

	}

	CBaseImageProcessor::~CBaseImageProcessor() {
	}

	GLuint CBaseImageProcessor::DrawFrame(GLuint srcTexID, int scWidth, int scHeight) {
		if (!m_isReady) {
			m_frameBuf = new UxFrameBuffer(scWidth,scHeight);
			m_vshString = FileUtil::loadShaderStr(vshPath);
			m_fshString = FileUtil::loadShaderStr(fshPath);
			m_programerID = CRenderUtil::loadProgram(m_vshString.c_str(), m_fshString.c_str());
			m_isReady = true;
		}

		PrepareToDraw();
		glUseProgram(m_programerID);
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
		//glBindTexture(GL_TEXTURE_2D, _texture->GetTexture());
		glBindTexture(GL_TEXTURE_2D, srcTexID);
		glUniform1i(_texcoordHandle, 0);

		m_frameBuf->bindFrameBuf();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_BYTE, indices);
		m_frameBuf->unBindFrameBuf();
		return m_frameBuf->getTexID();
	}

	void CBaseImageProcessor::PrepareToDraw() {
		glUseProgram(m_programerID);
		_positionHandle = glGetAttribLocation(m_programerID, "position");
		_texcoordHandle = glGetAttribLocation(m_programerID, "texcoord");
		_textureHandle = glGetUniformLocation(m_programerID, "texture");
	}

	//_programHandle = CRenderUtil::loadProgram(FileUtil::loadShaderStr("D:/Engine/EyeWorld/Eye3D/Resources/shaders/particle_vs.glsl").c_str(), FileUtil::loadShaderStr("D:/Engine/EyeWorld/Eye3D/Resources/shaders/particle_fs.glsl").c_str());
}
