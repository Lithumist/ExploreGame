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



	class EGMap
	{
	private:

		global* GlobalData;
		float playerStartX, playerStartY;
		IMetaTriangleSelector* meta;

	public:


		EGMap(global* data); // blank map
		EGMap(global* data, std::string filename); // loads a map from a file

		bool loadFromFile(std::string filename);

		void applyToSceneManager(ISceneManager* sm); // loads the map into the scene manager




		// get+set player start position
		void setPlayerStartX(float x);
		void setPlayerStartY(float y);
		float getPlayerStartX();
		float getPlayerStartY();

	};



}

#endif