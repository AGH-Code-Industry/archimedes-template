#include <systems/Competition.h>
#include <components/Competition.h>
#include <components/Particle.h>
#include <Defaults.h>
#include <Config.h>
#include <archimedes/Text.h>
#include <archimedes/Font.h>

namespace vs {

void CompetitionSystem::setup(Scene& scene) {
	auto buffer = defaultUniformBuffer();

	{
		auto max = scene.newEntity();
		max.addComponent(
			scene::components::TransformComponent{
				.position = {10.f, windowHeight - 100.f, -0.2f},
				.rotation = {0, 0, 0, 1},
				.scale = {100, 100, 0}
			}
		);
		max.addComponent<CompetitionMaxTextFlag<false>>();

		auto curr = scene.newEntity();
		curr.addComponent(
			scene::components::TransformComponent{
				.position = {10.f, windowHeight - 200.f, -0.2f},
				.rotation = {0, 0, 0, 1},
				.scale = {100, 100, 0}
			}
		);
		curr.addComponent<CompetitionCurrentTextFlag<false>>();
	}
	{
		auto max = scene.newEntity();
		max.addComponent(
			scene::components::TransformComponent{
				.position = {10.f + windowWidth / 2.f, windowHeight - 100.f, -0.2f},
				.rotation = {0, 0, 0, 1},
				.scale = {100, 100, 0}
			}
		);
		max.addComponent<CompetitionMaxTextFlag<true>>();

		auto curr = scene.newEntity();
		curr.addComponent(
			scene::components::TransformComponent{
				.position = {10.f + windowWidth / 2.f, windowHeight - 200.f, -0.2f},
				.rotation = {0, 0, 0, 1},
				.scale = {100, 100, 0}
			}
		);
		curr.addComponent<CompetitionCurrentTextFlag<true>>();
	}
}

void CompetitionSystem::update(Scene& scene) {
	static u32 maxParticlesLeft = 0;
	static u32 maxParticlesRight = 0;

	if (input::Keyboard::esc.down()) {
		maxParticlesLeft = 0;
		maxParticlesRight = 0;
	}

	{
		auto max = scene.entitiesWith<CompetitionMaxTextFlag<false>>().front();
		auto curr = scene.entitiesWith<CompetitionCurrentTextFlag<false>>().front();

		auto currParticles = scene.domain().components<Particle<false>>().base().count();
		maxParticlesLeft = std::max(maxParticlesLeft, currParticles);

		auto buffer = defaultUniformBuffer();

		max.removeComponent<text::TextComponent>();
		max.addComponent(
			text::TextComponent(
				text::convertTo<char32_t>(std::string_view(std::format("Max: {}", maxParticlesLeft))),
				{buffer},
				"Arial"
			)
		);
		curr.removeComponent<text::TextComponent>();
		curr.addComponent(
			text::TextComponent(
				text::convertTo<char32_t>(std::string_view(std::format("Current: {}", currParticles))),
				{buffer},
				"Arial"
			)
		);
	}
	{
		auto max = scene.entitiesWith<CompetitionMaxTextFlag<true>>().front();
		auto curr = scene.entitiesWith<CompetitionCurrentTextFlag<true>>().front();

		auto currParticles = scene.domain().components<Particle<true>>().base().count();
		maxParticlesRight = std::max(maxParticlesRight, currParticles);

		auto buffer = defaultUniformBuffer();

		max.removeComponent<text::TextComponent>();
		max.addComponent(
			text::TextComponent(
				text::convertTo<char32_t>(std::string_view(std::format("Max: {}", maxParticlesRight))),
				{buffer},
				"Arial"
			)
		);
		curr.removeComponent<text::TextComponent>();
		curr.addComponent(
			text::TextComponent(
				text::convertTo<char32_t>(std::string_view(std::format("Current: {}", currParticles))),
				{buffer},
				"Arial"
			)
		);
	}


}

}