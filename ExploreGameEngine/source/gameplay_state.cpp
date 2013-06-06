// gameplay_state.cpp
#include "gameplay_state.h"



namespace explore
{






	// Static instance.
	StateGameplay  StateGameplay::instance;





	void StateGameplay::init(Engine* _engine)
	{
		// Initialize the gameplay manager.
		manager.init(_engine);

		// Register our lua functions.
		lua::registerFunctions(_engine);

		// Load a test level.
		manager.level_current.load("res/levels/test_map_1.egl","test_map_1",_engine);

		loaded_correctly = true;
	}

	void StateGameplay::free(Engine* _engine)
	{
		// Free the gameplay manager.
		manager.free(_engine);
	}





	void StateGameplay::pause()
	{
		std::cout << "pause\n";
	}

	void StateGameplay::resume()
	{
		std::cout << "resume\n";
	}










	void StateGameplay::events(Engine* _engine)
	{
		manager.events(_engine);
	}





	int StateGameplay::step(Engine* _engine)
	{
		manager.step(_engine);
		return 0;
	}





	void StateGameplay::draw(Engine* _engine)
	{
		// Crash guard.
		if(!loaded_correctly)
			return;

		_engine->getDriver()->beginScene(true, true, _engine->getSmgr()->getAmbientLight().toSColor());

		// Draw the game.
		manager.draw(_engine);

		_engine->getDriver()->endScene();
	}






}