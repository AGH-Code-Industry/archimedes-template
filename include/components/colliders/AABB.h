#pragma once

#include <archimedes/ArchMath.h>

using namespace arch;

namespace vs::coll {

struct AABB {
	float2 topLeft;
	float2 bottomRight;
};

}