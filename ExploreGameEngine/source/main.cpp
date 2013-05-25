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



int main()
{
	// Create global struct
	eg::global GlobalData;


	// Create the window and set caption
	IrrlichtDevice* device=createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640,480), 16, false, false, false, 0);
	if(!device)
		return 1;

	GlobalData.window_caption = L"ExploreGame";
	device->setWindowCaption(GlobalData.window_caption.c_str());

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();


	// - - - - - - - - - - - - -
	//   Load basic resources
	// - - - - - - - - - - - - -

	// Load fonts
	GlobalData.fnt_trololol = NULL;
	GlobalData.fnt_trololol = guienv->getFont("res/fonts/trololol.xml");
	if(GlobalData.fnt_trololol == NULL)
	{
		device->drop();
		return 2;
	}



	IAnimatedMesh* mesh = smgr->getMesh("res/sydney.md2");
	if(!mesh)
	{
		device->drop();
		return 2;
	}
	
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);


	if(node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("res/sydney.bmp"));
	}




	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));




	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();

		GlobalData.fnt_trololol->draw(L"Explore Game",rect<s32>(64,32,400,64),SColor(255,255,255,255));

		driver->endScene();
	}





	device->drop();
	return 0;


}