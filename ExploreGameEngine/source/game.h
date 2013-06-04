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







#define PLAYER_STARTING_HP 100

#define PLAYER_HP_BAR_X 8
#define PLAYER_HP_BAR_Y 640
#define PLAYER_HP_BAR_FULL_WIDTH 128
#define PLAYER_HP_BAR_HEIGHT 8








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




		bool kDownPrev;




		void init();


	public:



		EGGame();
		EGGame(eg::global* data);


		void setData(eg::global* data);


		void startGameplay(GAME_START_TYPE type);


		bool damagePlayer(int dmg); // returns true when player is dead

		int step();
		void draw();





	};



}





#endif