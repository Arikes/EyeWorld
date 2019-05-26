#ifndef H_GAUSSBLUR_FILTER_H
#define H_GAUSSBLUR_FILTER_H
#include "BaseImageProcessor.h"
namespace UxDeepEye {
	class CGaussBlurFilter :public CBaseImageProcessor {
	public:
		CGaussBlurFilter();
		~CGaussBlurFilter();

	protected:

	private:
		void PrepareToDraw() override;
	};
}
#endif