#pragma once

#include <archimedes/ArchMath.h>

using namespace arch;

namespace vs {

template<u32 L>
struct LayerCollisionFlag {
	static constexpr u32 layer = L;
	static constexpr bool flagComponent = true;
};

}