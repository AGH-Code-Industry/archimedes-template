#pragma once

#include <random>
#include <archimedes/Scene.h>
#include <components/Wulkan.h>

using namespace arch;

namespace vs {

struct ParticleSystem {
	static void setup(Scene& scene, Entity particle, Wulkan& wulkan);
	static void update(ecs::Domain& domain);
};

}