/*
* 
* 
* 
* Explore Game Engine
* 
* 
* Pedro Custodio 2013
* 
* 
* 
* 
*/





#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#ifndef EG_DEBUG_MODE
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#endif







#include "game.h"
#include "globals.h"
#include "log.h"
#include "eg_map.h"
#include "save.h"
#include "lua_wrap.h"







int step(eg::global* data);
void draw(eg::global* data);









int main()
{
	// Open log file
	eg::log::open("log.txt");
	eg::log::log("Explore Game engine started");


	// Create global struct
	eg::global GlobalData;


	// Set state to initial loading
	GlobalData.current_state = 0;


	// Create the window and set caption
	GlobalData.window_width = 960;
	GlobalData.window_height = 656;
	GlobalData.device = createDevice(video::EDT_OPENGL, dimension2d<u32>(GlobalData.window_width,GlobalData.window_height), 16, false, false, false, &GlobalData.receiver);
	if(!GlobalData.device)
	{
		eg::log::error("Unable to create Irrlicht device");
		eg::log::close();
		return 1;
	}
	eg::log::log("Created Irrlicht device");

	GlobalData.window_caption = L"ExploreGame";
	GlobalData.device->setWindowCaption(GlobalData.window_caption.c_str());

	GlobalData.driver = GlobalData.device->getVideoDriver();
	GlobalData.smgr = GlobalData.device->getSceneManager();
	GlobalData.guienv = GlobalData.device->getGUIEnvironment();
	eg::log::log("Window set up");


	// Set the filename to use when saving and loading games
	GlobalData.savegameFilename = "savegame.dat";


	// Initialize lua
	GlobalData.lua.Init();


	// - - - - - - - - - - - - -
	//   Load basic resources
	// - - - - - - - - - - - - -

	// Load fonts
	GlobalData.fnt_trololol = NULL;
	GlobalData.fnt_trololol = GlobalData.guienv->getFont("res/fonts/trololol.xml");
	if(GlobalData.fnt_trololol == NULL)
	{
		eg::log::error("Unable to load font file res/fonts/trololol.xml");
		GlobalData.lua.Free();
		GlobalData.device->drop();
		eg::log::close();
		return 2;
	}
	eg::log::log("Loaded font file res/fonts/trololol.xml");


	// - - - - - - - - - - - - -
	//           End
	// - - - - - - - - - - - - -






	// Create the game manager
	eg::EGGame game(&GlobalData);
	GlobalData.g = &game;


	// Set state to main menu
	GlobalData.current_state = 1;


	// Main loop
	while(GlobalData.device->run())
	{

		// step
		int rtn = step(&GlobalData);
		if(rtn != 0)
		{
			GlobalData.device->drop();
			GlobalData.lua.Free();
			eg::log::close();
			return rtn;
		}

		// draw
		draw(&GlobalData);
	}






	// Exit
	eg::log::log("Explore Game engine exited");
	GlobalData.device->drop();
	GlobalData.lua.Free();
	eg::log::close();
	return 0;


}








void draw(eg::global* data)
{


	switch(data->current_state)
	{
		case 0: // initial loading
		break;

		case 1: // main menu

			data->driver->beginScene(true, true, SColor(255,100,101,140));
	
			data->fnt_trololol->draw(L"Explore Game",rect<s32>(64,32,400,64),SColor(255,255,255,255));
			data->fnt_trololol->draw(L"N - new game",rect<s32>(128,128,400,64),SColor(255,255,255,255));
			data->fnt_trololol->draw(L"L - load game",rect<s32>(128,160,400,64),SColor(255,255,255,255));

			data->driver->endScene();

		break;

		case 2: // in gameplay
			

			eg::EGGame* gam;
			gam = data->g;
			gam->draw();

		break;
	}



}








int step(eg::global* data)
{


	switch(data->current_state)
	{
		case 0: // initial loading
		break;

		case 1: // main menu
			

			if(data->receiver.IsKeyDown(irr::KEY_KEY_N))
			{
				// start the gameplay manager
				eg::EGGame* gam;
				gam = data->g;
				gam->startGameplay(eg::NEW_GAME);

				// tell the main loop to step and render the gameplay
				data->current_state = 2;
			}




			if(data->receiver.IsKeyDown(irr::KEY_KEY_L))
			{
				// load game
				eg::EGSave sv;
				sv.LoadFromFile(data->savegameFilename,data->SaveData);

				// start the gameplay manager
				eg::EGGame* gam;
				gam = data->g;
				gam->startGameplay(eg::LOAD_GAME);

				// tell the main loop to step and render the gameplay
				data->current_state = 2;
			}


		break;



		case 2: // in gameplay

			eg::EGGame* gam;
			gam = data->g;
			int res = gam->step();

			if(res != 0)
				return res;

		break;

	}



	return 0;
}