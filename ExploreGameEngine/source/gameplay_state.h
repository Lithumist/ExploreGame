#ifndef GAMEPLAY_STATE_H
#define GAMEPLAY_STATE_H

/*
	gameplay_state.h
	
	Delcares class 'StateGameplay'

	A state that handles the actual gameplay.
*/




#include "game_state.h"

#include "gameplay_manager.h"
#include "lua_wrapper.h"




namespace explore
{




	class StateGameplay : public State
	{

		public:

			void init(Engine* _engine);
			void free(Engine* _engine);

			void pause();
			void resume();

			void events(Engine* _engine);
			int step(Engine* _engine);
			void draw(Engine* _engine);


			static StateGameplay* getInstance(){ return &instance; }

			GameplayManager* getManager(){ return &manager; }


		protected:

			StateGameplay(){}

		private:

			static StateGameplay instance;

			GameplayManager manager;


	};









	/*
		Lua functions.

		Implemented in 'lua_functions.cpp'

		Registered with function registerFunctions() in StateGameplay::init()
	*/

	/*
		To-Do List:
		* 
		* Add functions to get the camera and target position
		* 
	*/

	namespace lua
	{

		// Registers all functions.
		void registerFunctions(Engine* _engine);

		// Helper function to check the number of arguments passed to lua functions.
		int numArgs(lua_State* l);
		
		// Helper function to push errors to lua.
		void pushError(lua_State* l, std::string error);

		// Camera control functions.
		int EG_DisplaceCameraPosition(lua_State* l);
		int EG_SetCameraPosition(lua_State* l);
		int EG_DisplaceCameraTargetPosition(lua_State* l);
		int EG_SetCameraTargetPosition(lua_State* l);

	}





}




#endif