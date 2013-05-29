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

			core::stringc name = node->getName();
			std::string rname = name.c_str();
			eg::log::log("###" + eg::ut::toString((int)i) +"###" + rname + "###");

			if((const char*)node->getName() == "MeshVisual")
			{
				gotVisual = true;
			}

			else if(node->getName() == "MeshPhysics")
			{
				gotPhysics = true;
				selector = GlobalData->smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			}

			else if(node->getName() == "MeshStart") // TODO: handle multiple start meshes, make camera start from these coordinates
			{
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