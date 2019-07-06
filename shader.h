
#pragma once

#include <GL/glew.h>

#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class shader{

	private:
		unsigned int ID = 0;
		std::string loadshader(const std::string& path);

	public:
		shader(const std::string& vs_path, const std::string& fs_path);
		~shader();
		void bind();
		void unbind();
		void setU1i(const std::string& name, int value) const;
		void setU1f(const std::string& name, float value) const;
		void setUmat4f(const std::string& name, const glm::mat4& value) const;
};
