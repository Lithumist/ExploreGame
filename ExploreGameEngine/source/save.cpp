// save.cpp
#include "save.h"




namespace eg
{
	

	EGSave::EGSave()
	{
		// nothing to be done
	}




	// Load
	void EGSave::LoadFromFile(const std::string& filename, savedata& dat)
	{
		std::ifstream in(filename.c_str());
		in.read(reinterpret_cast<char*>(&dat), sizeof(savedata));
	}




	// Save
	void EGSave::SaveToFile(const std::string& filename, const savedata& dat)
	{
		std::ofstream out(filename.c_str());
		out.write(reinterpret_cast<const char*>(&dat), sizeof(savedata));
	}


}