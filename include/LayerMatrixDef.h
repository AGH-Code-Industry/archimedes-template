#pragma once

#ifdef LAYER_SYSTEM_DEFINED
#error "LayerSystem included before LayerMatrix"
#endif

#include <systems/colliders/LayerMatrix.h>

namespace vs::coll {

consteval std::vector<std::vector<u8>> layerMatrix() {
	return {
		{1, 0},
		{0}
	};
}

}