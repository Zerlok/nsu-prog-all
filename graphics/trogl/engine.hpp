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

		// Methods.
		void setGUI(const GUIPtr& gui);
		void setDisplayFPS(bool displayFPS);
		void setActiveScene(const ScenePtr& scene);

		void showScene();

	protected:
		// Inner classes.
		class SingleVertexObject;

		using EngineObjects = std::list<SingleVertexObject>;
		using GUIfpsPtr = SharedPointer<GUIfps>;

		// Methods.
		void assignMeshToEngineObject(const MeshPtr& mesh);

		void initGeometry();
		void deinitGeometry();

		void initShaders();
		void deinitShaders();

		void drawGUI();
		void drawGUILabel(const GUILabel& glabel);
		void drawGUIPlane(const GUIPlane& gplane);

		void renderFrame();

		// Fields.
		ScenePtr _scene;
		GUIPtr _gui;
		GUIfpsPtr _guiFPS;
		EngineObjects _objects;
		bool _isValid;
		float _width;
		float _height;

	private:
		// Static fields.
		static const ShaderPtr DEFAULT_VERTEX_SHADER;
		static const ShaderPtr DEFAULT_FRAGMENT_SHADER;

		static Engine* _current;

		// Static methods.
		static void display();
		static void reshape(int w, int h);
		static void cycle();
		static std::string _generateWindowName(const Scene& scene);
		static bool _runGlewTest();
};


class Engine::SingleVertexObject
{
	public:
		SingleVertexObject(const MeshPtr& mesh);
		SingleVertexObject(SingleVertexObject&& obj);
		~SingleVertexObject();

		bool validate() const;

		bool compileShaders();
		void loadGeometry();
		void loadShaders();

		void unloadGeometry();
		void unloadShaders();

		void draw(const glm::mat4x4& mat);

	private:
		// Static fields.
		static const size_t _vertexStep;
		static const size_t _colorStep;
		static const size_t _indexStep;

		// OpenGL attributes.
		GLuint _glVBO;				// Vertex Buffer Object
		GLuint _glCBO;				// Color Buffer Object
		GLuint _glIBO;				// Index Buffer Object
		GLuint _glVertexShader;		// Vertices rendering
		GLuint _glFragmentShader;	// Faces rendering.
		GLuint _glShaderProgram;	// Total shadering program.
		GLuint _attrConstColor;		// Shader const color.
		GLuint _attrObjCenterPosition; // Shader center position of object.
		size_t _glShadersCompileCount;

		// Object attributes.
		std::vector<GLfloat> _vertices;
		std::vector<GLfloat> _colors;
		std::vector<GLuint> _indicies;

		ShaderPtr _vertexShader;
		ShaderPtr _fragmentShader;

		MeshPtr _mesh;

		// Methods.
		bool _compileVertexShader();
		bool _compileFragmentShader();
		bool _compileShaderProgram();
};


void reshape(int w, int h);
void cycle();


#endif // __ENGINE_HPP__
