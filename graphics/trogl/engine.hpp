#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include "core/opengls.hpp"
#include "core/shader.hpp"
#include "core/light.hpp"
#include "core/mesh.hpp"
#include "core/camera.hpp"
#include "core/scene.hpp"

#include "core/gui.hpp"
#include "gui/guilabel.hpp"
#include "gui/guiplane.hpp"
#include "gui/guifps.hpp"


class Engine
{
	public:
		// Constructors / Destructor.
		Engine(const bool& displayFPS = false);
		~Engine();

		// Methods.
		void setGUI(const GUIPtr& gui);
		void setDisplayFPS(const bool& displayFPS);
		void setActiveScene(const ScenePtr& scene);

		bool validateScene();
		void showScene();

	protected:
		// Inner classes.
		class VertexObject;
		class LightObject;

		using EngineObjects = std::list<VertexObject>;
		using GUIfpsPtr = SharedPointer<GUIfps>;

		// Methods.
		void drawGUI();
		void drawGUILabel(const GUILabel& glabel);
		void drawGUIPlane(const GUIPlane& gplane);

		void renderFrame();

		// Fields.
		int _glWindow;
		bool _wasValidated;

		ScenePtr _scene;
		GUIPtr _gui;
		GUIfpsPtr _guiFPS;

		EngineObjects _objects;

		float _width;
		float _height;

	private:
		// Static fields.
		static const ShaderPtr DEFAULT_VERTEX_SHADER;
		static const ShaderPtr DEFAULT_FRAGMENT_SHADER;

		static Engine* _current;

		// Static methods.
		static void _display();
		static void _cycle();
		static void _reshape(int w, int h);
		static bool _runGlewTest();
		static std::string _generateWindowName(const Scene& scene);
};

void reshape(int w, int h);
void cycle();


class Engine::VertexObject
{
	public:
		// Constructors / Destructor.
		VertexObject(const MeshPtr& mesh);
		VertexObject(VertexObject&& obj);
		~VertexObject();

		// Methods.
		bool isValid() const;
		void compileGLShaders();
		void initGLGeometry();

		void draw(const LightPtr& light);

	private:
		// Static fields.
		static const size_t _vertexStep;
		static const size_t _colorStep;
		static const size_t _indexStep;

		// OpenGL attributes.
		GLuint _glVBO;				// Vertex Buffer Object
		GLuint _glNBO;				// Vertex Normals Buffer Object
		GLuint _glCBO;				// Color Buffer Object
		GLuint _glIBO;				// Index Buffer Object

		GLuint _attrTestColor;

		Mesh::IndexingType _indexType;
		size_t _indicesSize;
		ShaderPtr _shader;

		// FIXME: do not use non-const MeshPtr.
		MeshPtr _mesh;

		// Methods.
		bool _isGLGeometryValid() const;

		void _initVertexBufferObject();
		void _initColorBufferObject();
		void _initIndexBufferObject();
		void _deinitGLGeometry();
};


class Engine::LightObject
{
	public:
		// Constructrs / Destructor.
		LightObject(const LightPtr& light);
		LightObject(LightObject&& obj);
		~LightObject();

		// Methods.
		bool isValid() const;
		void compileGLShaders();

	private:
		ShaderPtr _shader;
};


#endif // __ENGINE_HPP__
