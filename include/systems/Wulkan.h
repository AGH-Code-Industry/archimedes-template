#pragma once

#include <archimedes/Scene.h>

using namespace arch;

namespace vs {

struct WulkanSystem {
	static void setup(Entity wulkan, input::Key& key, bool isRight);
	static void update(Scene& scene);
};

}