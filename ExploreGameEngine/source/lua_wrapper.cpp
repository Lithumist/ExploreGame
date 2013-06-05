// lua_wrap.cpp
#include "lua_wrapper.h"

#include "log.h"




namespace explore{







LuaWrap LuaWrap::instance;






// Default constructor
LuaWrap::LuaWrap()
{
	state = NULL;
}


// Initializes lua and registers functions from LuaWrap class
void LuaWrap::init()
{
	state = luaL_newstate();
	luaL_openlibs(state);

	registerFunction("EG_Log", luaLog);
}


// Free memory used by lua
void LuaWrap::free()
{
	lua_close(state);
}





// Register function to call from lua
void LuaWrap::registerFunction(std::string name, lua_CFunction function)
{
	lua_register(state, name.c_str(), function);
}





// Execute a lua script
void LuaWrap::executeScript(std::string filename)
{
	log::log("Running lua script " + filename);
	luaL_dofile(state, filename.c_str());
	log::log("Finished lua script " + filename);
}






// Execute some given lua code
void LuaWrap::executeCode(std::string lua_code)
{
	log::log("Executing lua code: " + lua_code);
	luaL_dostring(state,lua_code.c_str());
	log::log("Finished executing lua code");
}
















// Wrap the logging function to LUA
int LuaWrap::luaLog(lua_State* l)
{
	int n = lua_gettop(l);
	if(n != 1)
	{
		lua_pushstring(l, "EG_Log only takes 1 argument.");
		lua_error(l);
		return 0;
	}


	std::string msg = lua_tostring(l,1); // first argument is index 1


	log::log(msg);


	return 0;
}











}