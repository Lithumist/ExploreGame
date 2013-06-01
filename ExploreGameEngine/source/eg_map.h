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
#include "lua_wrap.h"




#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;






#define ACTION_TRIGGER_RANGE 50





namespace eg
{




	class mapspot
	{
	public:

		mapspot();
		mapspot(float X, float Y, float Z);

		float x,y,z;
	};




	class triggercollision
	{
	public:

		triggercollision();
		triggercollision(float X, float Y, float Z, core::aabbox3d<float> BOX, std::string filename);
		void setData(float X, float Y, float Z, core::aabbox3d<float> BOX, std::string filename);

		bool PointInside(float X, float Y, float Z);
		bool BoundingBoxInside(core::aabbox3d<float> box);
		
		float x,y,z;
		core::aabbox3d<float> bbox;
		std::string luafilename;
	};





	class triggeraction
	{
	public:

		triggeraction();
		triggeraction(float X, float Y, float Z, std::string filename);
		void setData(float X, float Y, float Z, std::string filename);

		bool CloseEnough(float X, float Y, float Z);

		float x,y,z;
		std::string luafilename;
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
		std::vector<triggercollision> collisionTriggers;
		std::vector<triggeraction> actionTriggers;



		void setUpKeyMap();

	public:


		EGMap();
		EGMap(global* data); // blank map
		EGMap(global* data, std::string filename, std::string map_name); // loads a map from a file


		void clear(); // must be called before any other maps are loaded


		void setData(global* data);


		bool loadFromFile(std::string filename, std::string map_name);




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