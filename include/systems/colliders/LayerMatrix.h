#pragma once

#include <array>
#include <archimedes/Mmath.h>

#ifdef LAYER_SYSTEM_DEFINED
#error "LayerSystem included before LayerMatrix"
#endif

using namespace arch;

namespace vs::coll {

consteval std::vector<std::vector<u8>> layerMatrix();

consteval bool layerMatrix(u32 l1, u32 l2);
consteval u32 layerCount();

}

#include "LayerMatrix.hpp"