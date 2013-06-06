// lua_functions.cpp
#include "gameplay_state.h"




namespace explore
{
namespace lua{



	// Registers all functions.
	void registerFunctions(Engine* _engine)
	{
		_engine->getLua()->registerFunction("EG_DisplaceCameraPosition",EG_DisplaceCameraPosition);
		_engine->getLua()->registerFunction("EG_EG_SetCameraPosition",EG_SetCameraPosition);
		_engine->getLua()->registerFunction("EG_DisplaceCameraTarget",EG_DisplaceCameraTargetPosition);
		_engine->getLua()->registerFunction("EG_SetCameraTarget",EG_SetCameraTargetPosition);
	}



	// Helper function to check the number of arguments passed to lua functions.
	int numArgs(lua_State* l)
	{
		return lua_gettop(l);

	}



	// Helper function to push errors to lua.
	void pushError(lua_State* l, std::string error)
	{
		lua_pushstring(l, error.c_str());
		lua_error(l);
	}






	// Camera control functions.

	int EG_DisplaceCameraPosition(lua_State* l)
	{
		if(numArgs(l) != 3)
		{
			pushError(l,"EG_DisplaceCameraPosition takes 3 arguments");
			return 1;
		}

		StateGameplay* s = StateGameplay::getInstance();
		s->getManager()->getLevel()->moveCamera((float)lua_tonumber(l,1),(float)lua_tonumber(l,2),(float)lua_tonumber(l,3));
		return 0;
	}

	int EG_SetCameraPosition(lua_State* l)
	{
		if(numArgs(l) != 3)
		{
			pushError(l,"EG_SetCameraPosition takes 3 arguments");
			return 1;
		}

		StateGameplay* s = StateGameplay::getInstance();
		s->getManager()->getLevel()->setCameraPosition((float)lua_tonumber(l,1),(float)lua_tonumber(l,2),(float)lua_tonumber(l,3));
		return 0;
	}

	int EG_DisplaceCameraTargetPosition(lua_State* l)
	{
		if(numArgs(l) != 3)
		{
			pushError(l,"EG_DisplaceCameraTarget takes 3 arguments");
			return 1;
		}

		StateGameplay* s = StateGameplay::getInstance();
		s->getManager()->getLevel()->moveCameraTarget((float)lua_tonumber(l,1),(float)lua_tonumber(l,2),(float)lua_tonumber(l,3));
		return 0;
	}

	int EG_SetCameraTargetPosition(lua_State* l)
	{
		if(numArgs(l) != 3)
		{
			pushError(l,"EG_SetCameraTarget takes 3 arguments");
			return 1;
		}

		StateGameplay* s = StateGameplay::getInstance();
		s->getManager()->getLevel()->setCameraTarget((float)lua_tonumber(l,1),(float)lua_tonumber(l,2),(float)lua_tonumber(l,3));
		return 0;
	}




}} // End both namespaces.