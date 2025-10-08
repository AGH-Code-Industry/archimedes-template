#include <systems/Explosion.h>
#include <random>
#include <Config.h>
#include <Defaults.h>
#include <archimedes/Font.h>
#include <archimedes/Text.h>
#include <components/BoomTextTime.h>
#include <components/Wulkan.h>
#include <components/Kill.h>
#include <systems/Particle.h>
#include <chrono>

namespace vs {

void ExplosionSystem::makeText(Scene& scene) {
	static auto rng = std::mt19937(std::random_device{}());
	static auto fontSizeDist = std::uniform_real_distribution(75.f, 150.f);
	static auto angleDist = std::uniform_real_distribution(75.f, 150.f);
	static const auto margin = 100.f;
	static auto xDist = std::uniform_real_distribution(0.f, windowWidth - margin);
	static auto yDist = std::uniform_real_distribution(0.f, windowHeight - margin);

	auto boomText = scene.newEntity();
	boomText.addComponent(
		scene::components::TransformComponent{
			.position = float3{xDist(rng), yDist(rng), -0.2f},
			.rotation = glm::angleAxis(angleDist(rng), zAxis()),
			.scale = fontSizeDist(rng) * float3 { 1, 1, 0 }
		}
	);
	boomText.addComponent(
		text::TextComponent(U"BOOM!", {defaultUniformBuffer()}, *font::FontDB::get()["Arial"]->bold())
	);
	boomText.addComponent<BoomTextTime>(std::chrono::high_resolution_clock::now());
}

void ExplosionSystem::updateText(ecs::Domain& domain) {
	auto now = std::chrono::high_resolution_clock::now();
	domain.view<const text::TextComponent, const BoomTextTime>().forEach([&domain, &now](ecs::Entity entity, const BoomTextTime& time) {
		if (now - time.value >= std::chrono::seconds(1)) {
			domain.addComponent<Kill>(entity);
		}
	});
}

void ExplosionSystem::makeExplosion(Scene& scene, Entity wulkan) {
	auto&& wulkanComp = wulkan.getComponent<Wulkan>();

	for (u32 i = 0; i != wulkanComp.particleCount; ++i) {
		ParticleSystem::setup(scene, wulkan.addChild(), wulkanComp);
	}

	makeText(scene);
}

}