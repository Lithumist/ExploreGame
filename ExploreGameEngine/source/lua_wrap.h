#ifndef LUA_WRAP_H
#define LUA_WRAP_H

/*
	lua_wrap.h

	Declares class 'LuaWrap'

	Facilitates lua scripting intigration
*/








#include <iostream>
#include <fstream>


extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}


#include "log.h"









class LuaWrap
{
private:

	lua_State* state;


public:


	LuaWrap();

	void Init();
	void Free();


	void RegisterFunction(std::string name, lua_CFunction function);

	void ExecuteScript(std::string filename);

	void ExecuteCode(std::string lua_code);


	static int LuaLog(lua_State* l);


	lua_State* GetState();


};





#endif