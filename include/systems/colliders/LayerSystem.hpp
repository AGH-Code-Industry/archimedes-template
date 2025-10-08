#include "LayerSystem.h"

#define LAYER_SYSTEM_DEFINED

#include "LayerMatrix.h"
#include <tuple>
#include <archimedes/Ecs.h>
#include <components/colliders/LayeredAABB.h>
#include "AABBSystem.h"
#include <components/colliders/LayerCollisionFlag.h>

namespace vs::coll {

namespace detail {

template<u32 I1, u32 I2, u32 End>
void iterate2(ecs::Domain& domain) {
	if constexpr (I2 < End) {
		if constexpr (layerMatrix(I1, I2)) {
			// Logger::debug("{}:{}", I1, I2);
			for (auto&& [entity1, aabb1] : domain.view<LayeredAABB<I1>>().all()) {
				for (auto&& [entity2, aabb2] : domain.view<LayeredAABB<I2>>().all()) {
					if (AABBSystem::areColliding(aabb1, aabb2)) {
						domain.addComponent<LayerCollisionFlag<I2>>(entity1);
						domain.addComponent<LayerCollisionFlag<I1>>(entity2);
					}
				}
			}
		}
		iterate2<I1, I2 + 1, End>(domain);
	}
}

template<u32 I1, u32 End>
void iterate1(ecs::Domain& domain) {
	if constexpr (I1 < End) {
		iterate2<I1, I1, End>(domain);
		iterate1<I1 + 1, End>(domain);
	}
}

}

inline void LayerSystem::update(ecs::Domain& domain) {
	detail::iterate1<0, layerCount()>(domain);
}

}