#ifndef EXPLORE_CUSTOM_EVENT_RECEIVER_H
#define EXPLORE_CUSTOM_EVENT_RECEIVER_H

/*
	event_receiver.h

	declares class 'EGEventReceiver'

	Allows the rest of the engine to handle events.
*/



/*
	To-Do List:

	*
	* Make an 'isKeyPressed' method.
	*
*/



#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



namespace explore
{




	class EventReceiver : public IEventReceiver
	{


	public:
		virtual bool OnEvent(const SEvent& event);
		virtual bool IsKeyDown(EKEY_CODE keyCode) const;
		EventReceiver();



	private:
		bool KeyIsDown[KEY_KEY_CODES_COUNT];


	};





}




#endif