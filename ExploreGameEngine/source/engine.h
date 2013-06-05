#ifndef ENGINE_H
#define ENGINE_H



/*
	engine.h

	Declares 'Engine' class

	A class that manages States.
*/





#include <vector>
#include <string>



#include "custom_event_receiver.h"



#include <irrlicht.h>



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace explore
{



	// Forward declaration to be able to create pointers.
	class State;




	class Engine
	{
		public:


			bool init();
			void free();

			void changeState(State* _new_state);
			void pushState(State* _new_state);
			void popState();

			void events();
			int step();
			void draw();

			void exit(){ running = false; }

			bool isRunning(){ return running; }




			IrrlichtDevice* getDevice(){ return device; }
			IVideoDriver* getDriver(){ return driver; }
			ISceneManager* getSmgr(){ return smgr; }
			IGUIEnvironment* getGuienv(){ return guienv; }
			EventReceiver* getReceiver(){ return &receiver; }






		private:

			// If the engine is running or not.
			bool running;

			// The state stack.
			std::vector<State*> states;



			// The window information.
			unsigned int window_width, window_height;
			std::wstring window_caption;



			// Irrlicht pointers and objects.
			IrrlichtDevice* device;
			IVideoDriver* driver;
			ISceneManager* smgr;
			IGUIEnvironment* guienv;
			EventReceiver receiver;



	};




}

#endif