#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "opengls.hpp"
#include "scene.hpp"
#include "gui.hpp"
#include "shader.hpp"


// TODO: make all data as pointers!
class TroglEngine
{
	public:
		TroglEngine();
		virtual ~TroglEngine();

		// TODO: shader to material -> material for each object!
		void setVertextShader(Shader* vs);
		void setFragmentShader(Shader* fs);

		void setGUI(GUI* gui);
		void setActiveScene(const ScenePtr& scene);

		void showScene(); // runs GL.

	protected:
		ScenePtr _scene;
		GUI* _gui;

		void assignGeometry(const MeshPtr& mesh);

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
		bool runGlewTest();

		bool _isValid;

		float _width;
		float _height;

		GLuint _glVertexShader;
		GLuint _glFragmentShader;
		GLuint _glShaderProgram;

		GLuint _glVBO; // Vertex Buffer Object
		GLuint _glCBO; // Color Buffer Object
		GLuint _glIBO; // Index Buffer Object

		// TODO: remove this attribute (or place it into shader).
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
