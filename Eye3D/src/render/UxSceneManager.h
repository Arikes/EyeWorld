#pragma once
#include "../common.h"
#include "UxBetaParticle.h"
#include "../Object.h"
namespace UxDeepEye {
	class UxSceneManager {
	public:
		UxSceneManager();
		~UxSceneManager();

		void DrawFrame();
	private:
		//std::vector<>
		UxBetaParticle * m_betaParticle;
		Object * testObj;
	};
}