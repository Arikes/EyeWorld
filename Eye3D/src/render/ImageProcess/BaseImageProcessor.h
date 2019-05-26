#ifndef H_BASE_IMAGEPROCESSOR_H
#define H_BASE_IMAGEPROCESSOR_H

#include "../../common.h"
#include "../Texture.h"
#include "../../util/RenderUtil.h"
#include "../../util/FileUtil.h"
#include "../UxFrameBuffer.h"
namespace UxDeepEye {
	class CBaseImageProcessor {
	public:
		CBaseImageProcessor(const char* vsh, const char* fsh);

		~CBaseImageProcessor();

		GLuint DrawFrame(GLuint srcTexID,int scWidth,int scHeight);

	protected:
		GLuint GetProgragID() { return m_programerID; }
		virtual void PrepareToDraw();
	private:
		UxFrameBuffer * m_frameBuf;
		GLuint m_programerID;

		GLuint _positionHandle;
		GLuint _texcoordHandle;

		GLuint _textureHandle;
		CTexture *_texture;

		std::string m_vshString;
		std::string m_fshString;

		bool m_isReady;
	};
}

#endif