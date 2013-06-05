#ifndef GAME_STATE_H
#define GAME_STATE_H



/*
	game_state.h

	Declares 'State' class.

	A base class (mainly an interface) for all game states to inherit from.
*/




#include "engine.h"



namespace explore
{





	class State
	{
		public:

			virtual void init() = 0;
			virtual void free() = 0;

			virtual void pause() = 0;
			virtual void resume() = 0;

			virtual void events(Engine* _engine) = 0;
			virtual int step(Engine* _engine) = 0;
			virtual void draw(Engine* _engine) = 0;


			void ChangeState(Engine* _engine, State* _state)
			{
				_engine->changeState(_state);
			}


		protected:

			State(){}

	};







}

#endif