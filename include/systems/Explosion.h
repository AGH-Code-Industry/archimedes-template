#pragma once

#include <archimedes/Scene.h>

using namespace arch;

namespace vs {

struct ExplosionSystem {
	static void makeText(Scene& scene);
	static void updateText(ecs::Domain& domain);
	static void makeExplosion(Scene& scene, Entity wulkan);

	static void setupListener(Scene& scene, Entity wulkan1, Entity wulkan2);
};

}