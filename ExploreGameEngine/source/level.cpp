// level.cpp
#include "level.h"

#include "log.h"
#include "utils.h"




namespace explore
{




	// Constructor.
	Level::Level()
	{
		engine = NULL;
	}



	// Load the level into the scene manager.
	void Level::load(std::string _filename, std::string _level_name, Engine* _engine)
	{

		// Clear any old map data (if any).
		clear();


		// Store the engine pointer and level name.
		engine = _engine;
		level_name = _level_name;


		// Define loading flags.
		bool got_starting = false;


		// Log the start of loading.
		log::log("Loading level " + _filename);


		// Initialize the bullet world.
		_engine->getBp()->setWorldGravity(vector3df(0.0f,-10.0f,0.0f));


		// Add the map filesystem and construct the local path.
		// TODO: Find out if adding the same archive multiple times causes some problems.
		engine->getDevice()->getFileSystem()->addFileArchive(_filename.c_str());
		local_path = level_name + "/";


		// Load the .irr file.
		std::string irr_path = local_path + level_name + ".irr";
		if(!engine->getSmgr()->loadScene(irr_path.c_str()))
		{
			log::error("Couldn't load level " + _filename);
			return;
		}









		// Proccess each scene node.
		core::array<scene::ISceneNode*> nodes;
		engine->getSmgr()->getSceneNodesFromType(scene::ESNT_ANY, nodes);
		for(u32 n=0; n<nodes.size(); n++)
		{

			// Get a pointer to the current node.
			ISceneNode* node = nodes[n];


			// Do some black magic to make the node's names comparable.
			core::stringc oname = node->getName();
			std::string node_name = oname.c_str();


			// Log the node.
			log::log("Node number " + utils::toString((int)n) + " '" + node_name + "'");



			if(node_name == "MeshStart")
			{
				// Starting mesh.
				if(got_starting)
					log::warning("Multiple staring meshes");

				got_starting = true;
				start_x = node->getPosition().X;
				start_y = node->getPosition().Y;
				start_z = node->getPosition().Z;

				node->setVisible(false);
			}





			if(node_name == "MeshPhysics")
			{
				IMeshSceneNode* msn = (IMeshSceneNode*)node;
				engine->getBp()->addTrimesh(msn,MESH_PHYSICS_MASS);
			}

			if(node_name == "MeshPhysicsFixed")
			{
				IMeshSceneNode* msn = (IMeshSceneNode*)node;
				engine->getBp()->addTrimesh(msn,0.0f);
			}





			if(node_name == "MeshPhysicsInvisible")
			{
				node->setVisible(false);

				IMeshSceneNode* msn = (IMeshSceneNode*)node;
				engine->getBp()->addTrimesh(msn,MESH_PHYSICS_MASS);
			}

			if(node_name == "MeshPhysicsInvisibleFixed")
			{
				node->setVisible(false);

				IMeshSceneNode* msn = (IMeshSceneNode*)node;
				engine->getBp()->addTrimesh(msn,0.0f);
			}




		}










		// Set camera position.
		camera = engine->getSmgr()->addCameraSceneNode(0, vector3df(start_x,start_y,start_z), vector3df(0,0,0));


		// Finished loading successfuly.
		is_loaded = true;
		log::log("Finished loading level");


	}

	








	void Level::clear()
	{
		if(!engine)
			return;

		// Clear the bullet world
		engine->getBp()->clear();

		// Clear the scene manager.
		engine->getSmgr()->clear();

		// Clear all strings.
		local_path = "";
		level_name = "";

		// Clear starting position.
		start_x = start_y = start_z = 0.0f;


		// Set is_loaded flag.
		is_loaded = false;
	}















	void Level::moveCamera(float _x_displacement, float _y_displacement, float _z_displacement)
	{
		camera->setPosition(vector3df(camera->getPosition().X+_x_displacement, camera->getPosition().Y+_y_displacement, camera->getPosition().Y+_y_displacement));
	}

	void Level::moveCameraTarget(float _x_displacement, float _y_displacement, float _z_displacement)
	{
		camera->setTarget(vector3df(camera->getTarget().X+_x_displacement, camera->getTarget().Y+_y_displacement, camera->getTarget().Y+_y_displacement));
	}

	void Level::setCameraPosition(float _x, float _y, float _z)
	{
		camera->setPosition(vector3df(_x,_y,_z));
	}

	void Level::setCameraTarget(float _x, float _y, float _z)
	{
		camera->setTarget(vector3df(_x,_y,_z));
	}












	void Level::step()
	{
		if(!is_loaded)
			return;

		// Step the physics simulation
		engine->getBp()->stepSimulation();

	}






	void Level::draw()
	{
		if(!is_loaded)
			return;

		engine->getSmgr()->drawAll();
	}






}