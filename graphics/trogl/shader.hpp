#ifndef SHADER_H
#define SHADER_H


#include <string>


class Shader
{
	public:
		Shader(const std::string& src);
		Shader(const Shader& sh);
		~Shader();

		const char* getSrcPtr() const;
		const std::string& getSrc() const;

	private:
		std::string _src;
};


#endif // SHADER_H
