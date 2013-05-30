#ifndef SAVE_H
#define SAVE_H

/*
	save.h

	declares class 'EGSave'

	This class handles saving data to game files. (saves and loads 'savedata' objects)
*/







/*
	Stuff not loading correctly?

	Use number suffixes!!!!




	Remember that the compiler assumes what type a number is.
	Sometimes this assumption isn't the same as yours.

	e.g:

	3.14	<- compiler will assume type 'double'
	3.14f	<- compiler now knows you ment type 'float'
*/







#include <iostream>
#include <string>
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