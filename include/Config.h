#pragma once

#include <archimedes/Mmath.h>
#include <archimedes/Input.h>

using namespace arch;

namespace vs {

extern u32 windowWidth;
extern u32 windowHeight;

struct Layers {
	enum Values {
		ground,
		particle
	};
};

extern std::string explosionSoundPath;

}