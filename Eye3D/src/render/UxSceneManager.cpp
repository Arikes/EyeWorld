#include "UxSceneManager.h"
namespace UxDeepEye {
	UxSceneManager::UxSceneManager() {
		m_betaParticle = new UxBetaParticle();
	}
	
	UxSceneManager::~UxSceneManager() {
	}

	void UxSceneManager::DrawFrame() {
		m_betaParticle->DrawFrame();
	}
}