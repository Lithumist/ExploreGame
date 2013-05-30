#ifndef EG_MAP_H
#define EG_MAP_H


/*
	eg_map.h

	declares class 'EGMap'

	Represents a game map that can be loaded in from a specially formatted .irr file
*/



#include <iostream>
#include <string>
#include <vector>
#include <map>




#include "globals.h"
#include "log.h"
#include "utils.h"




#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



namespace eg
{




	class mapspot
	{
	public:

		mapspot();
		mapspot(float X, float Y, float Z);

		float x,y,z;
	};




	class EGMap
	{
	private:

		global* GlobalData;
		float playerStartX, playerStartY, playerStartZ;
		IMetaTriangleSelector* meta;
		ICameraSceneNode* mapCamera;
		SKeyMap keymap[6];


		std::map<int,mapspot> mapSpots;



		void setUpKeyMap();

	public:


		EGMap();
		EGMap(global* data); // blank map
		EGMap(global* data, std::string filename); // loads a map from a file


		void clear(); // must be called before any other maps are loaded


		void setData(global* data);


		bool loadFromFile(std::string filename);




		// get+set player start position
		void setPlayerStartX(float x);
		void setPlayerStartY(float y);
		void setPlayerStartZ(float z);
		float getPlayerStartX();
		float getPlayerStartY();
		float getPlayerStartZ();

		// camera control
		ICameraSceneNode* getCamera();

	};



}

#endif