#include "UxBetaParticle.h"
#include "../util/FileUtil.h"
namespace UxDeepEye {
	UxBetaParticle::UxBetaParticle() {
		m_ready = false;
	}

	UxBetaParticle::~UxBetaParticle() {
	}

	void UxBetaParticle::DrawFrame() {
		if (!m_ready) {
			CfgShader();
			m_ready = true;
		}
		glUseProgram(_programHandle);
		GLfloat verts[] = {
			-0.3,-0.3,0.0,
			0.3,-0.3,0.0,
			-0.3,0.3,0.0,
			0.3,0.3,0.0
		};
		glEnableVertexAttribArray(_positionHandle);
		glVertexAttribPointer(_positionHandle, 3, GL_FLOAT, GL_FALSE, 0, verts);
		glEnableVertexAttribArray(_positionHandle);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_BLEND);
		glEnable(GL_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_POINTS, 0, 4);
		glDisable(GL_BLEND);
	}

	void UxBetaParticle::CfgShader() {
		_programHandle = CRenderUtil::loadProgram(FileUtil::loadShaderStr("D:/Engine/EyeWorld/Eye3D/Resources/shaders/particle_vs.glsl").c_str(), FileUtil::loadShaderStr("D:/Engine/EyeWorld/Eye3D/Resources/shaders/particle_fs.glsl").c_str());
		glUseProgram(_programHandle);
		_positionHandle = glGetAttribLocation(_programHandle, "position");
	}
}