// eg_map.cpp
#include "eg_map.h"




namespace eg
{













	//
	// mapspot
	//

	mapspot::mapspot()
	{
		x=y=z=0;
	}

	mapspot::mapspot(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}














	//
	// EGMap
	//



	// Default constructor
	EGMap::EGMap()
	{
		playerStartX = 0.0f;
		playerStartY = 0.0f;

		setUpKeyMap();
	}


	// Constructor with global data pointer
	EGMap::EGMap(global* data)
	{
		if(!data)
			eg::log::log("Bad pointer being passed to EGMap::EGMap(global* data)");

		GlobalData = data;
		playerStartX = 0.0f;
		playerStartY = 0.0f;

		setUpKeyMap();
	}



	// Clears the map
	void EGMap::clear()
	{
		mapSpots.clear();
		playerStartX = 0.0f;
		playerStartY = 0.0f;
	}



	// Loads map from a file
	EGMap::EGMap(global* data, std::string filename)
	{
		if(!data)
			eg::log::log("Bad pointer being passed to EGMap::EGMap(global* data, std::string filename)");

		GlobalData = data;
		setUpKeyMap();
		loadFromFile(filename);
	}




	void EGMap::setData(global* data)
	{
		if(!data)
			eg::log::log("Bad pointer being passed to EGMap::setData(global* data)");

		GlobalData = data;
	}







	// Set up WASD movement with space to jump and ctrl to crouch
	void EGMap::setUpKeyMap()
	{

		keymap[0].Action = EKA_MOVE_FORWARD;
		keymap[0].KeyCode = KEY_KEY_W;

		keymap[1].Action = EKA_MOVE_BACKWARD;
		keymap[1].KeyCode = KEY_KEY_S;
		
		keymap[2].Action = EKA_STRAFE_LEFT;
		keymap[2].KeyCode = KEY_KEY_A;

		keymap[3].Action = EKA_STRAFE_RIGHT;
		keymap[3].KeyCode = KEY_KEY_D;

		keymap[4].Action = EKA_JUMP_UP; // doesn't work
		keymap[4].KeyCode = KEY_SPACE;

		keymap[5].Action = EKA_CROUCH; // doesn't work
		keymap[5].KeyCode = KEY_LCONTROL;

		
	}








	// Loads map from a file
	bool EGMap::loadFromFile(std::string filename)
	{

		// Define tracking variables
		bool gotVisual = false;
		bool gotPhysics = false;
		bool gotStarting = false;
		bool error = false;


		// Clear old map data (if any)
		clear();


		// Log
		eg::log::log("Loading map " + filename);


		// Clear old scene
		GlobalData->smgr->clear();


		// Load .irr file
		GlobalData->smgr->loadScene(filename.c_str());


		// Create meta triangle selector
		meta = GlobalData->smgr->createMetaTriangleSelector();


		// Process each mesh type
		core::array<scene::ISceneNode*> nodes;
		GlobalData->smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes);
		for(u32 i=0; i<nodes.size(); i++)
		{
			ISceneNode* node = nodes[i];
			ITriangleSelector* selector = 0;

			// Do some trickery to convert the meshes name into a comparable string
			core::stringc name = node->getName();
			std::string rname = name.c_str();

			// Log for easy level debugging
			eg::log::log("Node number " + eg::ut::toString((int)i) +", name '" + rname + "'");

			if(rname == "MeshVisual")
			{
				gotVisual = true;
			}

			else if(rname == "MeshPhysics")
			{
				gotPhysics = true;
				selector = GlobalData->smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			}

			else if(rname == "MeshStart")
			{
				if(gotStarting)
					eg::log::warning("Multiple starting meshes");

				gotStarting = true;
				playerStartX = node->getPosition().X;
				playerStartY = node->getPosition().Y;
				playerStartZ = node->getPosition().Z;

				node->setVisible(false);
			}

			else if(rname.substr(0,rname.length()-4) == "MapSpot")
			{
				int id = ut::toNumber(rname.substr(rname.length()-4,rname.length()));
				eg::log::log("Map Spot with id " + ut::toString(id) + ". At " + ut::toString(node->getPosition().X) + "," + ut::toString(node->getPosition().Y) + "," +ut::toString(node->getPosition().Z));

				mapSpots[id] = mapspot(node->getPosition().X, node->getPosition().Y, node->getPosition().Z);
			}



			if(selector)
			{
				meta->addTriangleSelector(selector);
				selector->drop();
			}



		}//end for loop







		// Set up fps camera for collision
		mapCamera = GlobalData->smgr->addCameraSceneNodeFPS(0,50.0f,0.1f,-1,keymap, 6);
		ISceneNodeAnimator* anim = GlobalData->smgr->createCollisionResponseAnimator(meta,mapCamera, vector3df(10,15,10),vector3df(0,-2,0));
		meta->drop();
		mapCamera->addAnimator(anim);
		anim->drop();

		// Set camera position
		mapCamera->setPosition(vector3df(playerStartX,playerStartY,playerStartZ));






		// Print any necessary warnings
		if(!gotVisual)
		{
			error = true;
			eg::log::warning("No visual mesh found");
		}

		if(!gotPhysics)
		{
			error = true;
			eg::log::warning("No physics mesh found");
		}

		if(!gotStarting)
		{
			error = true;
			eg::log::warning("No starting mesh found");
		}





		// Log
		eg::log::log("Finished loading map " + filename);





		return !error;
	}










	// get+set player start position
	void EGMap::setPlayerStartX(float x){playerStartX = x;}
	void EGMap::setPlayerStartY(float y){playerStartY = y;}
	void EGMap::setPlayerStartZ(float z){playerStartZ = z;}
	float EGMap::getPlayerStartX(){return playerStartX;}
	float EGMap::getPlayerStartY(){return playerStartY;}
	float EGMap::getPlayerStartZ(){return playerStartZ;}




	// camera control
	ICameraSceneNode* EGMap::getCamera(){ return mapCamera; }



}