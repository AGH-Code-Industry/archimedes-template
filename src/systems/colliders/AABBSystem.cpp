#include <systems/colliders/AABBSystem.h>
#include <components/colliders/LayeredAABB.h>
#include <components/colliders/PrePhysicsPos.h>
#include <archimedes/physics/components/Moveable.h>
#include <LayerMatrixDef.h>

namespace vs::coll {

bool AABBSystem::areColliding(const AABB& collider1, const AABB& collider2) {
	return collider1.topLeft.x <= collider2.bottomRight.x && collider1.bottomRight.x >= collider2.topLeft.x &&
		collider1.topLeft.y >= collider2.bottomRight.y && collider1.bottomRight.y <= collider2.topLeft.y;
}

template<u32 I, u32 End>
void iterateLayeredFetch(ecs::Domain& domain) {
	if constexpr (I < End) {
		domain.view<LayeredAABB<I>, const physics::Moveable>().forEach([&domain](ecs::Entity entity, const physics::Moveable& movable) {
			domain.addComponent<PrePhysicsPos>(entity).value = movable.center.position;
		});
		iterateLayeredFetch<I + 1, End>(domain);
	}
}

template<u32 I, u32 End>
void iterateLayeredUpdate(ecs::Domain& domain) {
	if constexpr (I < End) {
		for (auto&& [aabb, movable, prePos] : domain.view<LayeredAABB<I>, const physics::Moveable, const PrePhysicsPos>().components()) {
			const auto delta = movable.center.position - prePos.value;
			aabb.topLeft += delta;
			aabb.bottomRight += delta;
		}
		iterateLayeredUpdate<I + 1, End>(domain);
	}
}

void AABBSystem::prePhysicsFetch(ecs::Domain& domain) {
	domain.view<AABB, const physics::Moveable>().forEach([&domain](ecs::Entity entity, const physics::Moveable& movable) {
		domain.addComponent<PrePhysicsPos>(entity).value = movable.center.position;
	});
	iterateLayeredFetch<0, layerCount()>(domain);
}

void AABBSystem::postPhysicsUpdate(ecs::Domain& domain) {
	for (auto&& [aabb, movable, prePos] : domain.view<AABB, const physics::Moveable, const PrePhysicsPos>().components()) {
		const auto delta = movable.center.position - prePos.value;
		aabb.topLeft += delta;
		aabb.bottomRight += delta;
	}
	iterateLayeredUpdate<0, layerCount()>(domain);
}

}