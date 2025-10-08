#include <systems/Kill.h>
#include <components/Kill.h>
#include <ranges>

namespace vs {

void KillSystem::update(Scene& scene) {
	for (auto&& entity : scene.domain().view<Kill>()
		| std::ranges::to<std::vector>()) {
		scene.removeEntity(entity);
	}
}

}