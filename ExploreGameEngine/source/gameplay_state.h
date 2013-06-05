#ifndef GAMEPLAY_STATE_H
#define GAMEPLAY_STATE_H

/*
	gameplay_state.h
	
	Delcares class 'StateGameplay'

	A state that handles the actual gameplay.
*/




#include "game_state.h"

#include "level.h"




namespace explore
{




	class StateGameplay : public State
	{

		public:

			void init(Engine* _engine);
			void free();

			void pause();
			void resume();

			void events(Engine* _engine);
			int step(Engine* _engine);
			void draw(Engine* _engine);


			static StateGameplay* getInstance(){ return &instance; }


		protected:

			StateGameplay(){}

		private:

			static StateGameplay instance;

			Level level_current;


	};




};




#endif