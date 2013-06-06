// lua_wrap.cpp
#include "lua_wrapper.h"

#include "log.h"




namespace explore{







LuaWrap LuaWrap::instance;






// Private constructor.
LuaWrap::LuaWrap()
{
	state = NULL;
}


// Initializes lua and registers functions from LuaWrap class.
void LuaWrap::init()
{
	state = luaL_newstate();
	luaL_openlibs(state);

	registerFunction("EG_Log", luaLog);
}


// Free memory used by lua.
void LuaWrap::free()
{
	lua_close(state);
}





// Register function to call from lua.
void LuaWrap::registerFunction(std::string name, lua_CFunction function)
{
	lua_register(state, name.c_str(), function);
}





// Execute a lua script.
void LuaWrap::executeScript(std::string filename)
{
	log::log("Compiling lua script " + filename);


	
	// Load and compiler lua script.
	int er = luaL_loadfile(state, filename.c_str());

	if(er)
	{
		// Error loading and/or compiling lua script.
		if(lua_isstring(state, lua_gettop(state)))
		{
			std::string error_msg = lua_tostring(state, lua_gettop(state));
			lua_pop(state, 1);

			log::error("Lua error, " + error_msg);
			return;
		}
	}
	else
	{
		// Run script.
		log::log("Running lua script " + filename);
		int er2 = lua_pcall(state, 0, LUA_MULTRET, 0);

		if(er2)
		{
			if(lua_isstring(state, lua_gettop(state)))
			{
				std::string error_msg = lua_tostring(state, lua_gettop(state));
				lua_pop(state, 1);

				log::error("Lua error, " + error_msg);
				return;
			}
		}
	}


	log::log("Finished lua script " + filename);
}






// Execute some given lua code.
void LuaWrap::executeCode(std::string lua_code)
{
	log::log("Executing lua code: " + lua_code);
	luaL_dostring(state,lua_code.c_str());
	log::log("Finished executing lua code");
}
















// Wrap the logging function to lua.
int LuaWrap::luaLog(lua_State* l)
{
	int n = lua_gettop(l);
	if(n != 1)
	{
		lua_pushstring(l, "EG_Log takes 1 argument.");
		lua_error(l);
		return 0;
	}


	std::string msg = lua_tostring(l,1); // First argument is index 1.


	log::log(msg);


	return 0;
}











}