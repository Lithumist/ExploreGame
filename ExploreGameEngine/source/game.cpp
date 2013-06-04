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

			// Set up player
			GlobalData->playerHp = PLAYER_STARTING_HP;
			GlobalData->playerMaxHp = PLAYER_STARTING_HP;
		}
		else if(type == LOAD_GAME)
		{
		}
	}
















	// damagePlayer
	bool EGGame::damagePlayer(int dmg)
	{
		GlobalData->playerHp -= dmg;
		if(GlobalData->playerHp < 0)
		{
			GlobalData->playerHp = -1;
			return true;
		}
		return false;
	}















	// Draw game
	void EGGame::draw()
	{

		if(!GlobalData->isPaused)
		{
			GlobalData->driver->beginScene(true, true, SColor(255,100,101,140));

			// Draw 3D scene
			GlobalData->smgr->drawAll();

				/////////////
				// Draw HUD
				/////////////

				// Draw HP bar
				float width = ((float)GlobalData->playerHp/(float)GlobalData->playerMaxHp)*(float)PLAYER_HP_BAR_FULL_WIDTH;
				GlobalData->driver->draw2DRectangle( rect<s32>(PLAYER_HP_BAR_X,PLAYER_HP_BAR_Y,PLAYER_HP_BAR_X+( PLAYER_HP_BAR_FULL_WIDTH ),PLAYER_HP_BAR_Y+PLAYER_HP_BAR_HEIGHT) , SColor(255,255,0,0) ,  SColor(255,255,0,0) ,  SColor(255,255,0,0) ,  SColor(255,255,0,0) );
				GlobalData->driver->draw2DRectangle( rect<s32>(PLAYER_HP_BAR_X,PLAYER_HP_BAR_Y,PLAYER_HP_BAR_X+( (int)width ),PLAYER_HP_BAR_Y+PLAYER_HP_BAR_HEIGHT) , SColor(255,0,255,0) ,  SColor(255,0,255,0) ,  SColor(255,0,255,0) ,  SColor(255,0,255,0) );

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
				// TODO: make it only execute once
				//GlobalData->lua.ExecuteScript(currentMap.actionTriggers[t].luafilename);
			}
		}





		// Test collision triggers
		// TODO: Fix this, idk but it seems to always think that the bounding boxes are touching.
		for(int t=0; t<currentMap.collisionTriggers.size(); t++)
		{
			if(currentMap.collisionTriggers[t].PointInside(currentMap.getCamera()->getPosition().X,currentMap.getCamera()->getPosition().Y,currentMap.getCamera()->getPosition().Z))
			{
				eg::log::log("Collision!");
				// TODO: make it only execute once
				//GlobalData->lua.ExecuteScript(currentMap.collisionTriggers[t].luafilename);
			}
		}





		// Test HP bar
		if(GlobalData->receiver.IsKeyDown(irr::KEY_KEY_K) && !kDownPrev)
		{
			eg::log::log("HP: " + ut::toString(GlobalData->playerHp));
			damagePlayer(1);
			eg::log::log("HP: " + ut::toString(GlobalData->playerHp));
		}


		kDownPrev = GlobalData->receiver.IsKeyDown(irr::KEY_KEY_K);



		return 0;

	}





}