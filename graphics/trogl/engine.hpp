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
		// Inner classes.
		enum RenderMode
		{
			POINTS = GL_POINT,
			EDGES = GL_LINE,
			POLYGONS = GL_POLYGON,
		};

		enum class Status
		{
			DIRTY = 0,
			VALIDATION_FAILED,
			VALIDATION_SUCCESSFUL,
			RENDERING_STARTED,
			RENDERING_FINISHED,
		};

		// Static methods.
		static Engine& instance();

		// Methods.
		bool wasValidated() const;
		bool isValid() const;
		bool isInvalid() const;
		bool isRunning() const;
		bool isStopped() const;
		const Status& getStatus() const;

		void setGUI(const GUIPtr& gui);
		void setActiveScene(const ScenePtr& scene);
		void setRenderMode(const RenderMode& mode);

		void enableFPS();
		void disableFPS();

		bool validate();
		void showScene();

	private:
		// Inner classes.
		class VertexObject;
		class LightObject;

		using EngineObjects = std::list<VertexObject>;
		using GUIfpsPtr = SharedPointer<GUIfps>;

		// Static methods.
		static void _displayFunc();
		static void _idleFunc();
		static void _reshapeFunc(int w, int h);
		static bool _runGlewTest();
		static std::string _generateWindowName(const Scene& scene);

		// Constructors / Destructor.
		Engine();
		Engine(const Engine&);
		~Engine();

		// Operators.
		Engine& operator=(const Engine&);

		// Methods.
		void drawGUI();
		void drawGUILabel(const GUILabel& glabel);
		void drawGUIPlane(const GUIPlane& gplane);

		void renderFrame();

		// Fields.
		Status _status;

		int _glWindow;
		RenderMode _glRenderMode;

		float _frameWidth;
		float _frameHeight;

		GUIPtr _gui;
		GUIfpsPtr _guiFPS;

		ScenePtr _scene;
		CameraPtr _camera;

		EngineObjects _objects;
};


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
