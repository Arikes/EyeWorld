#include "UxFrameBuffer.h"
namespace UxDeepEye {
	UxFrameBuffer::UxFrameBuffer(int width, int height):m_screenWidth(width),m_screenHeight(height){
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_screenWidth, m_screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

		glGenFramebuffers(1, &m_frameBufID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufID);
	}
	
	UxFrameBuffer::~UxFrameBuffer() {
	
	}

	void UxFrameBuffer::bindFrameBuf() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);

	}
	void UxFrameBuffer::unBindFrameBuf() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint UxFrameBuffer::getTexID() {

		return m_textureID;
	}
}
