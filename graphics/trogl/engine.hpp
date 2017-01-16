#ifndef __ENGINE_HPP__
#define __ENGINGE_HPP__


#include <list>
#include <string>
#include <sharedpointer.h>

#include "core/opengls.hpp"
#include "core/component.hpp"
#include "core/animation.hpp"
#include "core/shader.hpp"
#include "core/material.hpp"
#include "core/mesh.hpp"
#include "core/primitive.hpp"

#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/scene.hpp"
#include "core/frame.hpp"

#include "core/gui.hpp"
#include "gui/guilabel.hpp"
#include "gui/guiplane.hpp"
#include "gui/guifps.hpp"

#include "common/peripherals.hpp"


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
		void setActiveFrame(const FramePtr& frame);
		void setRenderMode(const RenderMode& mode);

		void enableFPS();
		void disableFPS();

		Keyboard& getKeyboard();
		Mouse& getMouse();

		bool validate();
		void showActiveScene();

	private:
		// Inner classes.
		using Primitives = std::list<Primitive>;
		using GUIfpsPtr = SharedPointer<GUIfps>;

		// Static methods.
		static void _displayFunc();
		static void _idleFunc();
		static void _reshapeFunc(int width, int height);
		static void _kbLetterDownFunc(unsigned char key, int, int);
		static void _kbLetterUpFunc(unsigned char key, int x, int);
		static void _kbSpecialDownFunc(int key, int, int);
		static void _kbSpecialUpFunc(int key, int, int);
		static void _mouseClickFunc(int button, int state, int x, int y);
		static void _mouseActiveMotionFunc(int x, int y);
		static void _mousePassiveMotionFunc(int x, int y);
		static void _debugGL();

		static std::string _generateWindowTitle(const Scene& scene);
		static std::string _toString(const GLenum& type);

		// Constructors / Destructor.
		Engine();
		Engine(const Engine&);
		~Engine();

		// Operators.
		Engine& operator=(const Engine&);

		// Methods.
		void _logEngineOptions() const;
		void _logSceneStatistics() const;

		int _validateScene();
		int _validateFrame();
		int _validatePrimitives();
		int _validateKeyboard();
		int _validateMouse();

		void _glEnableOptions();
		void _glUpdateMatrices();

		void _viewGUI();
		void _viewFrame();

		// Fields.
		Status _status;

		RenderMode _glRenderMode;
		std::string _glVersion;
		std::string _glShaderVersion;
		glm::mat4x4 _glMV;
		glm::mat4x4 _glMP;

		GUIPtr _gui;
		GUIfpsPtr _guiFPS;
		ScenePtr _scene;
		CameraPtr _camera;
		Primitives _primitives;
		FramePtr _frame;

		Keyboard& _keyboard;
		Mouse& _mouse;

		Animations _animations;
};


#endif // __ENGINE_HPP__
