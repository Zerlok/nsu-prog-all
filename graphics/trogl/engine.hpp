#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "opengls.hpp"
#include "scene.hpp"
#include "shader.hpp"


class TroglEngine
{
	public:
		TroglEngine();
		virtual ~TroglEngine();

		void setVertextShader(const Shader& vs);
		void setFaceShader(const Shader& fs);

		void setActiveScene(const Scene& scene);

		void showScene(); // runs GL.

	protected:
		Scene _scene;

		void assignGeometry(const Mesh& mesh);

		void initGeometry();
		void deinitGeometry();

		void initShaders();
		void deinitShaders();

		void drawMatrix(const glm::mat4x4& mat);
		void renderFrame();

	private:
		static const Shader DEFAULT_VERTEX_SHADER;
		static const Shader DEFAULT_FACE_SHADER;

		static TroglEngine* _current;
		static void draw();
		static void reshape(int w, int h);
		static std::string generateWindowName(const Scene& scene);

		bool _isValid;
		bool runGlewTest();

		float _width;
		float _height;

		GLuint _glVertexShader;
		GLuint _glFragmentShader;
		GLuint _glShaderProgram;

		GLuint _glVBO; // Vertex Buffer Object
		GLuint _glCBO; // Color Buffer Object
		GLuint _glIBO; // Index Buffer Object

		GLuint _attrConstColor;

		std::vector<GLfloat> _vertices;
		std::vector<GLfloat> _colors;
		std::vector<GLuint> _indicies;

		Shader _vertexShader;
		Shader _faceShader;
};


void reshape(int w, int h);
void renderCycle();


#endif // __ENGINE_HPP__
