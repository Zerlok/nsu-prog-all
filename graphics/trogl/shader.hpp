#ifndef __SHADER_HPP__
#define __SHADER_HPP__


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


#endif // __SHADER_HPP__
