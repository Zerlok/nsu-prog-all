#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "opengls.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "gui.hpp"
#include "gui/guilabel.hpp"
#include "gui/guiplane.hpp"
#include "gui/guifps.hpp"


class Engine
{
	public:
		Engine(bool displayFPS = false);
		virtual ~Engine();

		// TODO: shader to material -> material for each object!
		void setVertextShader(const ShaderPtr& vs);
		void setFragmentShader(const ShaderPtr& fs);

		void setDisplayFPS(bool displayFPS);

		void setGUI(const GUIPtr& gui);
		void setActiveScene(const ScenePtr& scene);

		void showScene(); // runs GL.

	protected:
		using GUIfpsPtr = SharedPointer<GUIfps>;

		ScenePtr _scene;
		GUIPtr _gui;
		GUIfpsPtr _guiFPS;

		void assignGeometry(const MeshPtr& mesh);

		void initGeometry();
		void deinitGeometry();

		void initShaders();
		void deinitShaders();

		void drawGUI();
		void drawGUILabel(const GUILabel& glabel);
		void drawGUIPlane(const GUIPlane& gplane);

		void drawMatrix(const glm::mat4x4& mat);
		void renderFrame();

	private:

		static const ShaderPtr DEFAULT_VERTEX_SHADER;
		static const ShaderPtr DEFAULT_FRAGMENT_SHADER;

		static Engine* _current;
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

		ShaderPtr _vertexShader;
		ShaderPtr _fragmentShader;
};


void reshape(int w, int h);
void cycle();


#endif // __ENGINE_HPP__
