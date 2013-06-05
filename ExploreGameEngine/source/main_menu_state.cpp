// main_menu_state.cpp
#include "main_menu_state.h"

#include <iostream>




namespace explore
{




	// Static instance.
	StateMainMenu StateMainMenu::instance;





	void StateMainMenu::init(Engine* _engine)
	{
		loaded_correctly = true;

		// Load main menu font.
		font_comic = NULL;
		font_comic = _engine->getGuienv()->getFont(FONT_COMIC_PATH);
		if(!font_comic)
			loaded_correctly = false;
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
	}





	int StateMainMenu::step(Engine* _engine)
	{


		// Check for key presses
		if(_engine->getReceiver()->IsKeyDown(irr::KEY_KEY_N))
		{
		}


		if(_engine->getReceiver()->IsKeyDown(irr::KEY_KEY_L))
		{
		}


		return 0;
	}





	void StateMainMenu::draw(Engine* _engine)
	{
		// Crash guard.
		if(!loaded_correctly)
			return;

		_engine->getDriver()->beginScene(true, true, SColor(255,0,0,0));

		// Draw basic temporary main menu text.
		font_comic->draw(L"Explore Game",rect<s32>(64,32,400,64),SColor(255,255,255,255));
		font_comic->draw(L"N - new game",rect<s32>(128,128,400,64),SColor(255,255,255,255));
		font_comic->draw(L"L - load game",rect<s32>(128,160,400,64),SColor(255,255,255,255));

		_engine->getDriver()->endScene();
	}




}