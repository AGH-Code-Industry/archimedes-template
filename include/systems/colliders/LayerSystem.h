#pragma once

#include <components/colliders/LayeredAABB.h>

namespace vs::coll {

class LayerSystem {
public:
	static inline void update(ecs::Domain& domain);
};

}

#include "LayerSystem.hpp"