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

			core::stringc name = node->getName(); // TODO: why does this give "bad formated string"?!?!?!?!?!?
			eg::log::log(name.c_str());

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
			eg::log::log("No visual");

		if(!gotPhysics)
			eg::log::log("No physics");

		if(!gotStarting)
			eg::log::log("No starting");







		return true;
	}










	// get+set player start position
	void EGMap::setPlayerStartX(float x){playerStartX = x;}
	void EGMap::setPlayerStartY(float y){playerStartY = y;}
	float EGMap::getPlayerStartX(){return playerStartX;}
	float EGMap::getPlayerStartY(){return playerStartY;}



}