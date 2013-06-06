// gameplay_manager.cpp
#include "gameplay_manager.h"



namespace explore
{



	void GameplayManager::init(Engine* _engine)
	{
	}


	void GameplayManager::free(Engine* _engine)
	{
		// Clean the level up.
		level_current.clear();
	}










	void GameplayManager::events(Engine* _engine)
	{
	}






	void GameplayManager::step(Engine* _engine)
	{
	}






	void GameplayManager::draw(Engine* _engine)
	{
		// Draw the level main 3d scene.
		level_current.draw();
	}








}