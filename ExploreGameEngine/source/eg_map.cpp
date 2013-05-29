// eg_map.cpp
#include "eg_map.h"




namespace eg
{




	// Default constructor
	EGMap::EGMap(global* data)
	{
		if(!data)
			eg::log::log("Bad pointer being passed to EGMap::EGMap(global* data)");

		GlobalData = data;
		playerStartX = 0.0f;
		playerStartY = 0.0f;
	}



	// Loads map from a file
	EGMap::EGMap(global* data, std::string filename)
	{
		if(!data)
			eg::log::log("Bad pointer being passed to EGMap::EGMap(global* data, std::string filename)");

		GlobalData = data;
		loadFromFile(filename);
	}








	// Loads map from a file
	bool EGMap::loadFromFile(std::string filename)
	{

		// Define tracking variables
		bool gotVisual = false;
		bool gotPhysics = false;
		bool gotStarting = false;


		// Log
		eg::log::log("Loading map " + filename);


		// Clear old scene
		GlobalData->smgr->clear();


		// Load .irr file
		GlobalData->smgr->loadScene(filename.c_str());


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

			else if(rname == "MeshStart") // TODO: make camera start from these coordinates
			{
				if(gotStarting)
					eg::log::warning("Multiple starting meshes");

				gotStarting = true;
				playerStartX = node->getPosition().X;
				playerStartY = node->getPosition().Y;

				node->setVisible(false);
			}



			if(selector)
			{
				meta->addTriangleSelector(selector);
				selector->drop();
			}



		}//end for loop






		// Print any necessary warnings
		if(!gotVisual)
			eg::log::warning("No visual mesh found");

		if(!gotPhysics)
			eg::log::warning("No physics mesh found");

		if(!gotStarting)
			eg::log::warning("No starting mesh found");





		// Log
		eg::log::log("Finished loading map " + filename);

		return true;
	}










	// get+set player start position
	void EGMap::setPlayerStartX(float x){playerStartX = x;}
	void EGMap::setPlayerStartY(float y){playerStartY = y;}
	float EGMap::getPlayerStartX(){return playerStartX;}
	float EGMap::getPlayerStartY(){return playerStartY;}



}