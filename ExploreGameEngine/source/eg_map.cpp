// eg_map.cpp
#include "eg_map.h"




namespace eg
{




	// Default constructor
	EGMap::EGMap(global* data)
	{

		/*DEBUG MESSAGE*/
		#ifdef EG_DEBUG_MODE
		if(!data)
			std::cout << "DEBUG MESSAGE: Bad pointer being passed to EGMap::EGMap(global* data)\n";
		#endif
		/*END DEBUG MESSAGE*/

		GlobalData = data;
		playerStartX = 0.0f;
		playerStartY = 0.0f;
	}



	// Loads map from a file
	EGMap::EGMap(global* data, std::string filename)
	{

		/*DEBUG MESSAGE*/
		#ifdef EG_DEBUG_MODE
		if(!data)
			std::cout << "DEBUG MESSAGE: Bad pointer being passed to EGMap::EGMap(global* data)\n";
		#endif
		/*END DEBUG MESSAGE*/

		GlobalData = data;
		loadFromFile(filename);
	}








	// Loads map from a file
	bool EGMap::loadFromFile(std::string filename)
	{
		return false;
	}










	// get+set player start position
	void EGMap::setPlayerStartX(float x){playerStartX = x;}
	void EGMap::setPlayerStartY(float y){playerStartY = y;}
	float EGMap::getPlayerStartX(){return playerStartX;}
	float EGMap::getPlayerStartY(){return playerStartY;}



}