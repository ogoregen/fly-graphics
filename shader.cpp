
#include "shader.h"

shader::shader(const std::string& vs_path, const std::string& fs_path){
		
	int vs, fs;
	vs = glCreateShader(GL_VERTEX_SHADER);
	std::string vs_source = loadshader(vs_path);
	const char* vs_src = vs_source.c_str();
	glShaderSource(vs, 1, &vs_src, NULL);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fs_source = loadshader(fs_path);
	const char* fs_src = fs_source.c_str();
	glShaderSource(fs, 1, &fs_src, NULL);
	glCompileShader(fs);

	ID = glCreateProgram();
	glAttachShader(ID, vs);
	glAttachShader(ID, fs);
	glLinkProgram(ID);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

shader::~shader(){

	glDeleteProgram(ID);
}

void shader::bind(){

	glUseProgram(ID);
}

void shader::unbind(){

	glUseProgram(0);

}

void shader::setU1i(const std::string& name, int value) const{

	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setU1f(const std::string& name, float value) const{

	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setUmat4f(const std::string& name, const glm::mat4& value) const{

	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

std::string shader::loadshader(const std::string& path){

	std::ifstream stream(path);
	std::string line;
	std::stringstream ss;

	while(getline(stream, line)){

		ss << line << "\n";
	}

	return ss.str();
}
