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

#pragma once

#include "Types.h"
#include "PhysicsTypes.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

#include "PxPhysics.h"
#include "PxScene.h"
#include "PxRigidActor.h"

using physx::PxRigidActor;
using physx::PxMaterial;
using physx::PxScene;

namespace crown
{

struct PhysicsActor;
struct Quaternion;
struct Matrix4x4;
struct Unit;
class SceneGraph;

struct Actor
{
						Actor(const PhysicsActor& resource, PxScene* scene, SceneGraph& sg, int32_t node, const Vector3& pos, const Quaternion& rot);
						~Actor();

	void				enable_gravity();
	void				disable_gravity();

	bool				is_static() const;
	bool				is_dynamic() const;

	bool				is_kinematic() const;
	bool				is_physical() const;

	float				linear_damping() const;
	void				set_linear_damping(float rate);

	float				angular_damping() const;
	void				set_angular_damping(float rate);

	Vector3				linear_velocity() const;
	void				set_linear_velocity(const Vector3& vel);

	Vector3				angular_velocity() const;
	void				set_angular_velocity(const Vector3& vel);

	bool				is_sleeping();
	void				wake_up();

	void				update_pose();
	void				update(const Matrix4x4& pose);

private:

	void				create_sphere(const Vector3& position, float radius);
	void				create_box(const Vector3& position, float a, float b, float c);
	void				create_plane(const Vector3& position, const Vector3& normal);
	
public:

	const PhysicsActor&		m_resource;

	PxScene*				m_scene;
	SceneGraph&				m_scene_graph;
	int32_t					m_node;
	PxRigidActor* 			m_actor;
	PxMaterial* 			m_mat;
};

} // namespace crown