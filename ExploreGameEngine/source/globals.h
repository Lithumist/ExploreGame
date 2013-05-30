#ifndef GLOBALS_H
#define GLOBALS_H

/*
	globals.h

	declares struct 'global'

	stores all global varibles the whole program needs to know about.
*/


#include <string>


#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



#include "event_receiver.h"
#include "save.h"
#include "lua_wrap.h"



namespace eg
{

	class EGGame;

	struct global
	{
	public:

		// state info
		int current_state;

		// window info
		std::wstring window_caption;
		unsigned int window_width;
		unsigned int window_height;

		// irrlicht core objects
		IrrlichtDevice* device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;
		EGEventReceiver receiver;

		// fonts
		IGUIFont* fnt_trololol;

		// global savegame info
		savedata SaveData;
		std::string savegameFilename;

		// lua wrapper
		LuaWrap lua;

		// game manager
		eg::EGGame* g;

		// pause flags
		bool isPaused;
		bool escapePressedPrev;

	};

}



#endif