#include "UxSceneManager.h"
namespace UxDeepEye {
	UxSceneManager::UxSceneManager():testObj(nullptr){
		m_betaParticle = new UxBetaParticle();
		testObj = new Object();
	}
	
	UxSceneManager::~UxSceneManager() {
		//testObj->ReleaseRef();
		//delete testObj;
		//testObj = nullptr;
	}

	void UxSceneManager::DrawFrame() {
		m_betaParticle->DrawFrame();
	}
}