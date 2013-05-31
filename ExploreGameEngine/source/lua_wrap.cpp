// lua_wrap.cpp
#include "lua_wrap.h"







// Default constructor
LuaWrap::LuaWrap()
{
	state = NULL;
}


// Initializes lua and registers functions from LuaWrap class
void LuaWrap::Init()
{
	state = luaL_newstate();
	luaL_openlibs(state);

	RegisterFunction("EG_Log", LuaLog);
}


// Free memory used by lua
void LuaWrap::Free()
{
	lua_close(state);
}





// Register function to call from lua
void LuaWrap::RegisterFunction(std::string name, lua_CFunction function)
{
	lua_register(state, name.c_str(), function);
}





// Execute a lua script
void LuaWrap::ExecuteScript(std::string filename)
{
	eg::log::log("running script " + filename);
	luaL_dofile(state, filename.c_str());
	eg::log::log("finished script " + filename);
}






// Execute some given lua code
void LuaWrap::ExecuteCode(std::string lua_code)
{
	luaL_dostring(state,lua_code.c_str());
}











// Wrap the logging function to LUA
int LuaWrap::LuaLog(lua_State* l)
{
	int n = lua_gettop(l);
	if(n != 1)
	{
		lua_pushstring(l, "EG_Log only takes 1 argument.");
		lua_error(l);
		return 0;
	}


	std::string msg = lua_tostring(l,1); // first argument is index 1


	eg::log::log(msg);


	return 0;
}