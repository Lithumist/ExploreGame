#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

/*
	event_receiver.h

	declares class 'EGEventReceiver'

	Does shit lal
*/



#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



namespace eg
{




	class EGEventReceiver : public IEventReceiver
	{


	public:
		virtual bool OnEvent(const SEvent& event);
		virtual bool IsKeyDown(EKEY_CODE keyCode) const;
		EGEventReceiver();



	private:
		bool KeyIsDown[KEY_KEY_CODES_COUNT];


	};





}




#endif