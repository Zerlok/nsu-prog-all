#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "opengls.hpp"
#include "scene.hpp"


class TroglEngine
{
	public:
		TroglEngine();
		virtual ~TroglEngine();

		// OpenGL running.
		void setActiveScene(const Scene& scene);
		void showScene();

	protected:
		Scene _scene;

		float _width;
		float _height;

		GLuint _vertexShader;
		GLuint _fragmentShader;
		GLuint _shaderProgram;

		size_t _vboSize;
		size_t _cboSize;
		size_t _iboSize;

		GLuint _vbo; // Vertex Buffer Object
		GLuint _cbo; // Color Buffer Object
		GLuint _ibo; // Index Buffer Object

		GLuint _attrConstColor;

		void drawMatrix(const glm::mat4x4& mat);

		void initGeometry(const Mesh& mesh);
		void drawGeometry();
		void deinitGeometry();

		void initShaders();
		void deinitShaders();

	private:
		static TroglEngine* _current;
		static void draw();
		static void reshape(int w, int h);
		static std::string generateWindowName(const Scene& scene);

		bool _isValid;
		bool runGlewTest();
};


void reshape(int w, int h);
void renderCycle();


#endif // __ENGINE_HPP__
