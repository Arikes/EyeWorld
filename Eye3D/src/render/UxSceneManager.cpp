#include "UxSceneManager.h"
namespace UxDeepEye {
	UxSceneManager::UxSceneManager():testObj(nullptr), testModel(nullptr),testModelShader(nullptr){
		m_betaParticle = new UxBetaParticle();
		testObj = new Object();
	}
	
	UxSceneManager::~UxSceneManager() {
		//testObj->ReleaseRef();
		//delete testObj;
		//testObj = nullptr;
	}

	void UxSceneManager::DrawFrame() {

		if (this->testModel == nullptr) {
			//std::string path = "D:/Engine/EyeWorld/x64/Debug/models/duck.fbx";
			std::string path = "D:/Engine/EyeWorld/x64/Debug/models/jeep1.3ds";
			this->testModel = new Model(path);
		}

		if (this->testModelShader == nullptr) {
			this->testModelShader = new Shader("D:/Engine/EyeWorld/x64/Debug/models/model.vertex", "D:/Engine/EyeWorld/x64/Debug/models/model.frag");
		}
		m_betaParticle->DrawFrame();

		this->testModelShader->use();

		Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
		glm::mat4 projection = glm::perspective(glm::radians(75.0F), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		this->testModelShader->setMat4("projection", projection);
		this->testModelShader->setMat4("view", view);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, 0.0f, glm::vec3(1.0,0.0,0.0));

		float scaleRate = 0.7f;
		model = glm::scale(model, glm::vec3(scaleRate));	// it's a bit too big for our scene, so scale it down
		
		this->testModelShader->setMat4("model", model);

		this->testModel->Draw(*this->testModelShader);
	}
}