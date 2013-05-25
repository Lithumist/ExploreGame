#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif







#include "globals.h"








int step(eg::global* data);
void draw(eg::global* data);









int main()
{
	// Create global struct
	eg::global GlobalData;


	// Set state to initial loading
	GlobalData.current_state = 0;


	// Create the window and set caption
	GlobalData.window_width = 960;
	GlobalData.window_height = 656;
	GlobalData.device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(GlobalData.window_width,GlobalData.window_height), 16, false, false, false, 0);
	if(!GlobalData.device)
		return 1;

	GlobalData.window_caption = L"ExploreGame";
	GlobalData.device->setWindowCaption(GlobalData.window_caption.c_str());

	GlobalData.driver = GlobalData.device->getVideoDriver();
	GlobalData.smgr = GlobalData.device->getSceneManager();
	GlobalData.guienv = GlobalData.device->getGUIEnvironment();


	// - - - - - - - - - - - - -
	//   Load basic resources
	// - - - - - - - - - - - - -

	// Load fonts
	GlobalData.fnt_trololol = NULL;
	GlobalData.fnt_trololol = GlobalData.guienv->getFont("res/fonts/trololol.xml");
	if(GlobalData.fnt_trololol == NULL)
	{
		GlobalData.device->drop();
		return 2;
	}


	// - - - - - - - - - - - - -
	//           End
	// - - - - - - - - - - - - -






	// Main loop
	while(GlobalData.device->run())
	{

		// step
		int rtn = step(&GlobalData);
		if(rtn < 0)
		{
			GlobalData.device->drop();
			return rtn;
		}

		// draw
		draw(&GlobalData);
	}






	// Exit
	GlobalData.device->drop();
	return 0;


}








void draw(eg::global* data)
{
	data->driver->beginScene(true, true, SColor(255,100,101,140));
	
	data->fnt_trololol->draw(L"Explore Game",rect<s32>(64,32,400,64),SColor(255,255,255,255));
	data->fnt_trololol->draw(L"N - new game",rect<s32>(128,128,400,64),SColor(255,255,255,255));
	data->fnt_trololol->draw(L"L - load game",rect<s32>(128,160,400,64),SColor(255,255,255,255));

	data->driver->endScene();
}








int step(eg::global* data)
{
	return 0;
}