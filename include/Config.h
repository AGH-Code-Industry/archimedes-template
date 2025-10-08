#pragma once

#include <archimedes/Mmath.h>
#include <archimedes/Input.h>

using namespace arch;

namespace vs {

static constexpr u32 windowWidth = 1600;
static constexpr u32 windowHeight = 900;

struct Layers {
	enum Values {
		ground,
		particle
	};
};

}