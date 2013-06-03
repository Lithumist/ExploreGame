// game.cpp
#include "game.h"




namespace eg
{




	// On new game
	const std::string EGGame::firstMapFilename = "res/maps/test2";
	const std::string EGGame::firstMapName = "test2";





	// Default constructor
	EGGame::EGGame()
	{
		GlobalData = NULL;
	}




	// Constructor with global data pointer
	EGGame::EGGame(eg::global* data)
	{
		GlobalData = NULL;

		if(!data)
			eg::log::log("Bad pointer being passed to EGGame::EGGame(eg::global* data)");

		GlobalData = data;
		currentMap.setData(GlobalData);

		init();
	}





	// Set global data pointer
	void EGGame::setData(eg::global* data)
	{
		if(!data)
			eg::log::log("Bad pointer being passed to EGGame::setData(eg::global* data)");

		GlobalData = data;
		currentMap.setData(GlobalData);

		init();
	}











	// Private initialization function
	void EGGame::init()
	{
		if(!GlobalData)
		{
			eg::log::error("EGGame::init() can't execute because global data pointer is not defined");
			return;
		}


		GlobalData->isPaused = false;
		GlobalData->escapePressedPrev = false;

	}










	// Start game
	void EGGame::startGameplay(GAME_START_TYPE type)
	{
		if(type == NEW_GAME)
		{
			// Load test level
			currentMap.loadFromFile(EGGame::firstMapFilename, eg::EGGame::firstMapName);
		}
		else if(type == LOAD_GAME)
		{
		}
	}















	// Draw game
	void EGGame::draw()
	{

		if(!GlobalData->isPaused)
		{
			GlobalData->driver->beginScene(true, true, SColor(255,100,101,140));
			GlobalData->smgr->drawAll();
			GlobalData->driver->endScene();
		}

	}

















	// Step game
	int EGGame::step()
	{

		// Turn pause on/off
		if(!GlobalData->escapePressedPrev && GlobalData->receiver.IsKeyDown(KEY_ESCAPE))
		{
			GlobalData->isPaused = !GlobalData->isPaused;
			eg::log::log_iostream("toggle pause");
		}
		GlobalData->escapePressedPrev = GlobalData->receiver.IsKeyDown(KEY_ESCAPE);




		// Handle quitting from pause
		if(GlobalData->isPaused && GlobalData->receiver.IsKeyDown(KEY_KEY_Q))
		{
			eg::log::log("Quitting from pause screne");
			return 1;
		}






		// Prevent the rest of the code from running if the game is paused
		if(GlobalData->isPaused)
			return 0;






		// Test action triggers
		for(int t=0; t<currentMap.actionTriggers.size(); t++)
		{
			if(currentMap.actionTriggers[t].CloseEnough(currentMap.getCamera()->getPosition().X,currentMap.getCamera()->getPosition().Y,currentMap.getCamera()->getPosition().Z))
			{
				eg::log::log("Close!");
			}
		}




		return 0;

	}





}