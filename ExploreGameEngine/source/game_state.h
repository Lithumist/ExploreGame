#ifndef GAME_STATE_H
#define GAME_STATE_H



/*
	game_state.h

	Declares 'State' class.

	A base class (mainly an interface) for all game states to inherit from.
*/



namespace explore
{





	class State
	{
		public:

			virtual void init() = 0;
			virtual void free() = 0;

			virtual void pause() = 0;
			virtual void resume() = 0;

			virtual void events() = 0;
			virtual int step() = 0;
			virtual void draw() = 0;


		protected:

			State();

	};







}

#endif