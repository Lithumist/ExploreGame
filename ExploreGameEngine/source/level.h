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


			void moveCamera(float _x_displacement, float _y_displacement, float _z_displacement);
			void setCameraPosition(float _x, float _y, float _z);
			void setCameraTarget(float _x, float _y, float _z);






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