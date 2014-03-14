/*
Copyright (c) 2013 Daniele Bartolini, Michele Rossi
Copyright (c) 2012 Daniele Bartolini, Simone Boscaratto

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "LuaEnvironment.h"
#include "LuaStack.h"
#include "PhysicsWorld.h"
#include "Raycast.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace crown
{

//-----------------------------------------------------------------------------
CE_EXPORT int physics_world_gravity(lua_State* L)
{
	LuaStack stack(L);

	PhysicsWorld* world = stack.get_physics_world(1);

	stack.push_vector3(world->gravity());
	return 1;
}

//-----------------------------------------------------------------------------
CE_EXPORT int physics_world_set_gravity(lua_State* L)
{
	LuaStack stack(L);

	PhysicsWorld* world = stack.get_physics_world(1);
	const Vector3& gravity = stack.get_vector3(2);

	world->set_gravity(gravity);
	return 0;
}

//-----------------------------------------------------------------------------
CE_EXPORT int physics_world_make_raycast(lua_State* L)
{
	LuaStack stack(L);

	PhysicsWorld* world = stack.get_physics_world(1);
	const char* callback = stack.get_string(2);
	int mode = stack.get_int(3);
	int filter = stack.get_int(4);

	RaycastId raycast = world->create_raycast(callback, (SceneQueryMode::Enum) mode, (SceneQueryFilter::Enum) filter);

	stack.push_raycast(world->lookup_raycast(raycast));
	return 1;
}

//-----------------------------------------------------------------------------
CE_EXPORT int physics_world_overlap_test(lua_State* L)
{
	LuaStack stack(L);

	PhysicsWorld* world = stack.get_physics_world(1);
	const char* callback = stack.get_string(2);
	int mode = stack.get_int(3);
	int filter = stack.get_int(4);
	int shape_type = stack.get_int(5);
	Vector3 pos = stack.get_vector3(6);
	Quaternion rot = stack.get_quaternion(7);
	Vector3 size = stack.get_vector3(8);

	world->overlap_test(callback, (SceneQueryMode::Enum) mode, (SceneQueryFilter::Enum) filter,
						(ShapeType::Enum) shape_type, pos, rot, size);

	return 0;
}

//-----------------------------------------------------------------------------
CE_EXPORT int physics_world_sync_overlap_test(lua_State* L)
{
	LuaStack stack(L);

	PhysicsWorld* world = stack.get_physics_world(1);
	const char* callback = stack.get_string(2);
	int mode = stack.get_int(3);
	int filter = stack.get_int(4);
	int shape_type = stack.get_int(5);
	Vector3 pos = stack.get_vector3(6);
	Quaternion rot = stack.get_quaternion(7);
	Vector3 size = stack.get_vector3(8);

	Actor* actor = world->sync_overlap_test(callback, (SceneQueryMode::Enum) mode, (SceneQueryFilter::Enum) filter,
										(ShapeType::Enum) shape_type, pos, rot, size);

	if (actor)
		stack.push_actor(actor);
	else
		stack.push_nil();
	
	return 1;
}

//-----------------------------------------------------------------------------
void load_physics_world(LuaEnvironment& env)
{
	env.load_module_function("PhysicsWorld", "gravity",			physics_world_gravity);
	env.load_module_function("PhysicsWorld", "set_gravity",		physics_world_set_gravity);
	env.load_module_function("PhysicsWorld", "make_raycast",	physics_world_make_raycast);
	env.load_module_function("PhysicsWorld", "overlap_test",	physics_world_overlap_test);
	env.load_module_function("PhysicsWorld", "sync_overlap_test",	physics_world_sync_overlap_test);
}

} // namespace crown