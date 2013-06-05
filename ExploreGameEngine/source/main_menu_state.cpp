// main_menu_state.cpp
#include "main_menu_state.h"

#include <iostream>




namespace explore
{




	// Static instance.
	StateMainMenu StateMainMenu::instance;





	void StateMainMenu::init()
	{
		std::cout << "init\n";
	}

	void StateMainMenu::free()
	{
		std::cout << "free\n";
	}





	void StateMainMenu::pause()
	{
		std::cout << "pause\n";
	}

	void StateMainMenu::resume()
	{
		std::cout << "resume\n";
	}










	void StateMainMenu::events(Engine* _engine)
	{
		std::cout << "events\n";
	}





	int StateMainMenu::step(Engine* _engine)
	{
		std::cout << "step\n";
		return 0;
	}





	void StateMainMenu::draw(Engine* _engine)
	{
		_engine->getDriver()->beginScene(true, true, SColor(255,100,101,140));

		_engine->getDriver()->endScene();
	}




}