#ifndef ENGINE_H
#define ENGINE_H



/*
	engine.h

	Declares 'Engine' class

	A class that manages States.
*/





#include <vector>






namespace explore
{



	// Forward declaration to be able to create pointers.
	class State;




	class Engine
	{
		public:


			void init();
			void free();

			void changeState(State* _new_state);

			void events();
			int step();
			void draw();

			void exit();

			bool isRunning();






		private:

			bool running;


			std::vector<State*> states;




	};




}

#endif