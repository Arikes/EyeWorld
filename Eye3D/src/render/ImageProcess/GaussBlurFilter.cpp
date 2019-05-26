#include "GaussBlurFilter.h"

namespace UxDeepEye {
	CGaussBlurFilter::CGaussBlurFilter():CBaseImageProcessor("",""){
	}

	CGaussBlurFilter::~CGaussBlurFilter() {
	}

	void CGaussBlurFilter::PrepareToDraw() {
		CBaseImageProcessor::PrepareToDraw();
		GLuint flipHandle = glGetUniformLocation(CBaseImageProcessor::GetProgragID(), "flip");
		glUniform1i(flipHandle, 1);
		//flip
	}
}