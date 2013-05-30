// lua_wrap.cpp
#include "lua_wrap.h"







// Default constructor
LuaWrap::LuaWrap()
{
	state = NULL;
}


// Initializes lua
void LuaWrap::Init()
{
	state = luaL_newstate();
	luaL_openlibs(state);
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
	luaL_dofile(state, filename.c_str());
}






// Execute some given lua code
void LuaWrap::ExecuteCode(std::string lua_code)
{
	luaL_dostring(state,lua_code.c_str());
}