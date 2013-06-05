#ifndef LEVEL_H
#define LEVEL_H

/*
	level.h

	Declares class 'Level'

	Represents a level in the game. Provides methods to draw and step.
*/



#include "engine.h"


#include <string>





namespace explore
{







	class Level
	{

		public:


			Level();


			void load(std::string _filename, std::string _level_name, Engine* _engine);
			void clear();


			void step();
			void draw();


			// TODO: Add camera control and movement methods






		private:


			Engine* engine;
			bool is_loaded;


			std::string local_path;
			std::string level_name;


			float start_x, start_y, start_z;


			ICameraSceneNode* camera;

	};






}




#endif