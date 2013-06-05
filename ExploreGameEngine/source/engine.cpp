// engine.cpp
#include "engine.h"
#include "game_state.h"

namespace explore
{




	// Initializes the engine and low level systems.
	void Engine::init()
	{
		running = false;

		states.clear();
	}




	// Frees memory used by states and low level systems.
	void Engine::free()
	{
		// cleanup the all states
		while(!states.empty())
		{
			states.back()->free();
			states.pop_back();
		}
	}







	// Changes the engine's state to one new state.
	void Engine::changeState(State* _new_state)
	{
		if(!states.empty())
		{
			states.back()->free();
			states.pop_back();
		}

		states.push_back(_new_state);
		states.back()->init();
	}

	// Push a new state onto the state stack.
	void Engine::pushState(State* _new_state)
	{
		if(!states.empty())
		{
			states.back()->pause();
		}

		states.push_back(_new_state);
		states.back()->init();
	}

	// Pops the latest state off the stack.
	void Engine::popState()
	{
		if(!states.empty())
		{
			states.back()->free();
			states.pop_back();
		}

		if(!states.empty()) 
		{
			states.back()->resume();
		}
	}







	// Does events.
	void Engine::events()
	{
		for(unsigned int s=0; s<states.size(); s++)
		{
			states[s]->events();
		}
	}


	// Does logic.
	int Engine::step()
	{
		for(unsigned int s=0; s<states.size(); s++)
		{
			states[s]->step();
		}

		return 0;
	}


	// Does drawing.
	void Engine::draw()
	{
		for(unsigned int s=0; s<states.size(); s++)
		{
			states[s]->draw();
		}
	}





}