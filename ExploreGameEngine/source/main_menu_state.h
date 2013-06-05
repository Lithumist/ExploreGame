#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

/*

	main_menu_state.h

	Declares class 'StateMainMenu'

	The state the game is in when on the main menu.

*/






#include "game_state.h"






namespace explore
{







	class StateMainMenu : public State
	{

		public:

			void init();
			void free();

			void pause();
			void resume();

			void events(Engine* _engine);
			int step(Engine* _engine);
			void draw(Engine* _engine);


			static StateMainMenu* getInstance(){ return &instance; }


		protected:

			StateMainMenu(){}

		private:

			static StateMainMenu instance;

	};






}





#endif