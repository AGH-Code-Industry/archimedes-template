#include <systems/Ground.h>
#include <Config.h>
#include <Defaults.h>
#include <components/colliders/LayeredAABB.h>

namespace vs {

void GroundSystem::setup(Scene& scene) {
	auto&& aabb = scene.newEntity().addComponent<coll::LayeredAABB<Layers::ground>>();
	aabb.topLeft = float2{-1000000, 0};
	aabb.bottomRight = float2{windowWidth + 1000000, -1000};
}

}