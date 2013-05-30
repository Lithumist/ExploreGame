#ifndef SAVE_H
#define SAVE_H

/*
	save.h

	declares class 'EGSave'

	This class handles saving data to game files. (saves and loads 'savedata' objects)
*/



#include <iostream>
#include <string>
//#include <vector>
#include <fstream>




namespace eg
{







	struct savedata // POD
	{
		bool a;
		bool b;
		bool c;

		int number;


		float another_number;
	};







	class EGSave
	{
	private:
	public:


		EGSave();

		void LoadFromFile(const std::string& filename, savedata& dat);
		void SaveToFile(const std::string& filename, const savedata& dat);


	};


}




#endif