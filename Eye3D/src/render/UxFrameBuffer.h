#pragma once
#include "../util/RenderUtil.h"
namespace UxDeepEye {
	class UxFrameBuffer {
	public:
		UxFrameBuffer(int width,int height);
		~UxFrameBuffer();

		void bindFrameBuf();
		void unBindFrameBuf();

		GLuint getTexID();
	private:
		int m_screenWidth, m_screenHeight;
		GLuint m_textureID;
		GLuint m_frameBufID;
	};
}
