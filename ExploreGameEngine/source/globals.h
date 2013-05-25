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


namespace eg
{

	struct global
	{
	public:

		// window info
		std::wstring window_caption;

		// fonts
		IGUIFont* fnt_trololol;

	};

}



#endif