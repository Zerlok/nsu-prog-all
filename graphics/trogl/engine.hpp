#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include <list>
#include <string>
#include <sharedpointer.h>

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


class Frame
{
	public:
		Frame(const std::string& title,
			  const size_t& width = 0,
			  const size_t& height = 0);
		~Frame();

		const size_t& getWidth() const;
		const size_t& getHeight() const;

		bool validate() const;

		void resize(const size_t& width,
					const size_t& height);

		void clear(const Color& color);
		void flush();

	private:
		std::string _title;
		size_t _width;
		size_t _height;
		int _glWindow;

		GLuint _buffer;
		GLuint _frameTexture;
};

using FramePtr = SharedPointer<Frame>;


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
		bool isRunning() const;
		bool isStopped() const;
		const Status& getStatus() const;

		void setGUI(const GUIPtr& gui);
		void setActiveScene(const ScenePtr& scene);
		void setRenderMode(const RenderMode& mode);

		void enableFPS();
		void disableFPS();

		bool validate();
		void showActiveScene();

	private:
		// Inner classes.
		class VertexObject;
		class LightObject;

		using EngineObjects = std::list<VertexObject>;
		using GUIfpsPtr = SharedPointer<GUIfps>;

		// Static methods.
		static void _displayFunc();
		static void _idleFunc();
		static void _reshapeFunc(int width, int height);
		static bool _runGlewTest();
		static std::string _generateWindowTitle(const Scene& scene);

		// Constructors / Destructor.
		Engine();
		Engine(const Engine&);
		~Engine();

		// Operators.
		Engine& operator=(const Engine&);

		// Methods.
		void _logSceneStatistics() const;

		int _validateScene();
		int _validateFrame();
		int _validateMeshes();

		void _enableGLOptions();
		void _initGLProjectionMatrix();

		void _viewGUI();
		void _viewFrame();

		void _reshape(int width, int height);

		// Fields.
		Status _status;

		RenderMode _glRenderMode;

		GUIPtr _gui;
		GUIfpsPtr _guiFPS;
		ScenePtr _scene;
		CameraPtr _camera;
		EngineObjects _objects;

		FramePtr _frame;
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

		void draw(const LightPtr& light, const CameraPtr& camera);

	private:
		// Static fields.
		static const size_t _vertexStep;
		static const size_t _colorStep;
		static const size_t _indexStep;

		// OpenGL attributes.
		GLuint _glVBO; // Vertex Buffer Object
		GLuint _glNBO; // Vertex Normal Buffer Object
		GLuint _glCBO; // Color Buffer Object
		GLuint _glIBO; // Index Buffer Object

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


#endif // __ENGINE_HPP__
