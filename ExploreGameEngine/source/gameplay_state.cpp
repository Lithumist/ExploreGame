// gameplay_state.cpp
#include "gameplay_state.h"



namespace explore
{






	// Static instance.
	StateGameplay  StateGameplay::instance;





	void StateGameplay::init(Engine* _engine)
	{
		// Load a test level.
		level_current.load("res/levels/test_map_1.egl","test_map_1",_engine);

		loaded_correctly = true;
	}

	void StateGameplay::free()
	{
		std::cout << "free\n";
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
	}





	int StateGameplay::step(Engine* _engine)
	{

		level_current.moveCamera(0.0f,0.0f,0.0f);

		return 0;
	}





	void StateGameplay::draw(Engine* _engine)
	{
		// Crash guard.
		if(!loaded_correctly)
			return;

		_engine->getDriver()->beginScene(true, true, SColor(255,0,0,0));

		// Draw the 3d level scene.
		level_current.draw();

		_engine->getDriver()->endScene();
	}






}