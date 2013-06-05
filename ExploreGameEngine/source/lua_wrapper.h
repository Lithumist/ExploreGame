#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

/*
	lua_wrapper.h

	Declares class 'LuaWrap'

	Facilitates lua scripting intigration.
*/





#include <iostream>
#include <fstream>


extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}






namespace explore{


class LuaWrap
{
private:

	static LuaWrap instance;

	lua_State* state;
	LuaWrap();


public:


	static LuaWrap* getInstance(){ return &instance; }


	void init();
	void free();


	void registerFunction(std::string name, lua_CFunction function);

	void executeScript(std::string filename);

	void executeCode(std::string lua_code);


	static int luaLog(lua_State* l);


	lua_State* getState();


};



}


#endif