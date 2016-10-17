#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "opengls.hpp"
#include "scene.hpp"
#include "gui.hpp"
#include "shader.hpp"


class TroglEngine
{
	public:
		TroglEngine();
		virtual ~TroglEngine();

		// TODO: shader to material -> material for each object!
		void setVertextShader(Shader* vs);
		void setFragmentShader(Shader* fs);

		void setGUI(const GUI& gui);
		void setActiveScene(const Scene& scene);

		void showScene(); // runs GL.

	protected:
		GUI _gui;
		Scene _scene;

		void assignGeometry(const Mesh& mesh);

		void initGeometry();
		void deinitGeometry();

		void initShaders();
		void deinitShaders();

		void drawGUI();
		void drawMatrix(const glm::mat4x4& mat);
		void renderFrame();

	private:
		static Shader* DEFAULT_VERTEX_SHADER;
		static Shader* DEFAULT_FRAGMENT_SHADER;

		static TroglEngine* _current;
		static void display();
		static void reshape(int w, int h);
		static void cycle();

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

		Shader* _vertexShader;
		Shader* _fragmentShader;
};


void reshape(int w, int h);
void cycle();


#endif // __ENGINE_HPP__
