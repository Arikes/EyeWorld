#include "TestImage.h"
#include "../util/RenderUtil.h"
namespace UxDeepEye {
	CTestImage::CTestImage():_shaderReady(false){
	}

	CTestImage::~CTestImage() {
	}

	void CTestImage::DrawFrame(GLuint textureID) {
		if (!_shaderReady) {
			_programHandle = CRenderUtil::loadProgram(vsh, fsh);
			CfgShader();
			_texture = new CTexture("C:/Users/Aerk/Pictures/ResTest/hello.jpg");
			_shaderReady = true;
		}

		glUseProgram(_programHandle);
		//GLfloat verts[] = {
		//	-1.0,-1.0,0.0,
		//	1.0,-1.0,0.0,
		//	-1.0,1.0,0.0,
		//	1.0,1.0,0.0
		//};

		GLfloat verts[] = {
			-0.5,-0.5,0.0,
			0.5,-0.5,0.0,
			-0.5,0.5,0.0,
			0.5,0.5,0.0
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

		glVertexAttribPointer(_positionHandle, 3, GL_FLOAT,GL_FALSE, 0, verts);
		glEnableVertexAttribArray(_positionHandle);
		
		glVertexAttribPointer(_texcoordHandle, 2, GL_FLOAT,GL_FALSE, 0, texcoords);
		glEnableVertexAttribArray(_texcoordHandle);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture->GetTexture());
		glUniform1i(_texcoordHandle,0);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_BYTE, indices);

		std::cout << "CTestImage DrawFrame" << std::endl;
	}

	void CTestImage::CfgShader() {
		glUseProgram(_programHandle);
		_positionHandle = glGetAttribLocation(_programHandle, "position");
		_texcoordHandle = glGetAttribLocation(_programHandle, "texcoord");
		_textureHandle = glGetUniformLocation(_programHandle, "texture");
	}
}