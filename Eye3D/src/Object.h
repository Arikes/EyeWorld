#pragma once
#include "RefCount.h"
namespace UxDeepEye {
	class Object :public RefCounted {
	public:
		Object();
		~Object() override;
	};
}