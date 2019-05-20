#include "FileUtil.h"
#include <istream>
#include <fstream>
#include <sstream>
namespace UxDeepEye {
	std::string FileUtil::loadShaderStr(std::string shaderPath) {
		std::string retStr = "";
		std::ifstream iShaderStram(shaderPath.c_str(),std::ios::in);
		if (iShaderStram.is_open())
		{
			std::stringstream strTemp;
			strTemp << iShaderStram.rdbuf();
			retStr = strTemp.str();
			iShaderStram.close();
			return retStr;
		}
	}
}