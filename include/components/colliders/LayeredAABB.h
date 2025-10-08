#pragma once

#include "AABB.h"

namespace vs::coll {

template<u32 L>
struct LayeredAABB: public AABB {};

}