#pragma once

#include <components/colliders/AABB.h>
#include <archimedes/Ecs.h>

namespace vs::coll {

class AABBSystem {
public:
	static bool areColliding(const AABB& collider1, const AABB& collider2);

	static void prePhysicsFetch(ecs::Domain& domain);
	static void postPhysicsUpdate(ecs::Domain& domain);
};

}