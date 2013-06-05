// engine.cpp
#include "engine.h"
#include "game_state.h"
#include "log.h"

namespace explore
{




	// Initializes the engine and low level systems.
	bool Engine::init()
	{

		// Set the engine to be running and clear any states.
		running = false;
		states.clear();


		// Open the log file
		log_filename = "log.txt";
		log::open(log_filename);


		// Set up Irrlicht and the rendering window.
		window_width = 960;
		window_height = 656;
		device = createDevice(video::EDT_OPENGL, dimension2d<u32>(window_width,window_height), 16, false, false, false, &receiver);
		if(!device)
		{
			return false;
		}


		// Set the window caption.
		device->setWindowCaption(window_caption.c_str());


		// Set up pointers to all Irrlicht systems.
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		guienv = device->getGUIEnvironment();


		// Set up the lua system and do a test.
		lua = LuaWrap::getInstance();
		lua->init();
		lua->executeScript("test.lua");


		// Finished.
		return true;
	}




	// Frees memory used by states and low level systems.
	void Engine::free()
	{
		// Cleanup the all states.
		while(!states.empty())
		{
			states.back()->free();
			states.pop_back();
		}

		
		// Free Irrlicht.
		device->drop();


		// Free the lua system
		lua->free();
		lua = NULL;


		// Close the log file.
		log::close();
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
			states[s]->events(this);
		}
	}


	// Does logic.
	int Engine::step()
	{
		for(unsigned int s=0; s<states.size(); s++)
		{
			states[s]->step(this);
		}

		return 0;
	}


	// Does drawing.
	void Engine::draw()
	{
		for(unsigned int s=0; s<states.size(); s++)
		{
			states[s]->draw(this);
		}
	}











	// Runs the engine.
	int Engine::run()
	{
		running = true;


		while(device->run())
		{
			events();
			step();
			draw();
		}


		return 0;
	}





}