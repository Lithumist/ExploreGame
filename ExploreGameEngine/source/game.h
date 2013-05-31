#ifndef GAME_H
#define GAME_H

/*
	game.h

	Declares class 'EGGame'

	Manages the real gameplay at the highest level
*/






//#include <iostream>
//#include <string>
//#include <fstream>



#include "eg_map.h"
#include "globals.h"








namespace eg
{




	enum GAME_START_TYPE { NEW_GAME, LOAD_GAME };





	class EGGame
	{
	private:


		static const std::string firstMapName;
		static const std::string firstMapFilename; // The map that is loaded on 'new game'
		


		eg::global* GlobalData;
		eg::EGMap currentMap;


		void init();


	public:



		EGGame();
		EGGame(eg::global* data);


		void setData(eg::global* data);


		void startGameplay(GAME_START_TYPE type);

		int step();
		void draw();





	};



}





#endif