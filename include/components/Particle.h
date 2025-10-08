#pragma once

#include <archimedes/Mmath.h>

namespace vs {

template<bool IsRight>
struct Particle {
	glm::quat rotationQuat;
	float e;
	u32 collisionCounter = 0;
};

}