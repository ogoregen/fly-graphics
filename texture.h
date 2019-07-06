
#pragma once

class texture{

	private:
		unsigned int ID;

	public:
		int w, h;
		texture(const char* path);
		~texture();
		void bind();
		void unbind();
};
