#pragma once

#include <archimedes/Scene.h>

using namespace arch;

namespace vs {

struct CompetitionSystem {
	static void setup(Scene& scene);
	static void update(Scene& scene);
};

}