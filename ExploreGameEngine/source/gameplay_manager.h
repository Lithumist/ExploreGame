#ifndef GAMEPLAY_MANAGER_H
#define GAMEPLAY_MANAGER_H

/*
	gameplay_manager.h

	Declares class 'GameplayManager'

	Is declared and invoked by the gameplay state to manage the whole game.
	Note that this class is friends with the gameplay state to facilitate lua function binding.
*/


#include "level.h"



namespace explore
{





	// StateGameplay forward declaration.
	class StateGameplay;




	class GameplayManager
	{

		public:


			friend class StateGameplay;


			void init(Engine* _engine);
			void free(Engine* _engine);

			void events(Engine* _engine);
			void step(Engine* _engine);
			void draw(Engine* _engine);



			Level* getLevel(){ return &level_current; }



		private:



			Level level_current;


	};






}



#endif