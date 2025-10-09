#include <components/Wulkan.h>
#include <systems/Wulkan.h>
#include <MakeTexture.h>
#include <MakeMesh.h>
#include <Defaults.h>
#include <Config.h>
#include <systems/Explosion.h>
#include <archimedes/physics/components/Moveable.h>
#include <archimedes/audio/AudioSourceComponent.h>
#include <SoundManager.h>

namespace vs {

void setupAudioSource(Entity wulkan, const Wulkan& wulkanComp);

void WulkanSystem::setup(Entity wulkan, input::Key& key, bool isRight) {
	auto renderer = gfx::Renderer::getCurrent();

	auto wulkanTexture = makeTexture("textures/wulkan.png");
	auto particleTexture = makeTexture("textures/particle.png");

	const auto texWidth = wulkanTexture->getWidth();
	const auto texHeight = wulkanTexture->getHeight();

	auto mesh = makeMesh(std::span(defaultVertices()), std::span(defaultIndices()));
	auto pipeline = renderer->getPipelineManager()->create(
		gfx::pipeline::Pipeline::Desc{
			.vertexShaderPath = "shaders/vertex_default.glsl",
			.fragmentShaderPath = "shaders/fragment_default.glsl",
			.textures = {wulkanTexture},
			.buffers = {defaultUniformBuffer()},
		});
	auto particlePipeline = renderer->getPipelineManager()->create(
		gfx::pipeline::Pipeline::Desc{
			.vertexShaderPath = "shaders/vertex_default.glsl",
			.fragmentShaderPath = "shaders/fragment_default.glsl",
			.textures = {particleTexture},
			.buffers = {defaultUniformBuffer()},
		});

	const float scale = 0.25f;
	const float windowLeftSpace = (windowWidth - 2.f * scale * texWidth) / 3.f;
	auto&& transform = wulkan.addComponent(
		scene::components::TransformComponent{
			.position = float3{windowLeftSpace + isRight * (windowLeftSpace + texWidth * scale), texHeight * scale, 0},
			.rotation = {0, 0, 0, 1},
			.scale = scale * float3{texWidth, texHeight, 0},
		});
	wulkan.addComponent(
		scene::components::MeshComponent{
			.mesh = mesh,
			.pipeline = pipeline
		});

	using FloatDist = Wulkan::FloatDist;
	auto&& wulkanComponent = wulkan.addComponent(
		Wulkan{
			.particleCount = 200,
			.key = &key,
			.explosionAngleDist = FloatDist(glm::radians(-45.f), glm::radians(45.f)),
			.velocityDist = FloatDist(600.f, 1000.f),
			.rotationSpeedDist = FloatDist(glm::radians(-9.f), glm::radians(9.f)),
			.sizeDist = FloatDist(20.f, 40.f),
			.eDist = FloatDist(0.25f, 0.4f),
			.texture = wulkanTexture,
			.particlePipeline = particlePipeline,
			.particleMesh = makeMesh(std::span(defaultParticleVertices()), std::span(defaultIndices())),
			.particleOrigin = transform.position + float3{texWidth * scale / 2.f, 0, 0},
			.isRight = isRight
		}
	);

	setupAudioSource(wulkan, wulkanComponent);
}

void setupAudioSource(Entity wulkan, const Wulkan& wulkanComp) {
	auto source = wulkan.addChild();
	/*auto&& transform = source.addComponent(
		scene::components::TransformComponent{
			.position = wulkanComp.particleOrigin,
			.rotation = {0, 0, 0, 1},
			.scale = {1, 1, 0}
		}
	);*/
	//auto&& movable = source.addComponent<physics::Moveable>();
	auto&& sourceComp = source.addComponent<audio::AudioSourceComponent>();
	sourceComp.path = explosionSoundPath;
	sourceComp.isLooped = false;
	sourceComp.rolloffFactor = 0.01f;
	sourceComp.dontRemoveFinished = false;
	auto&& soundManager = scene::SceneManager::get()->currentScene()->domain().global<SoundManager>();
	soundManager.audioManager->assignSource(sourceComp/*, transform, movable*/);
}

void WulkanSystem::update(Scene& scene) {
	for (auto&& [entity, wulkan] : scene.domain().view<Wulkan>().all()) {
		if (wulkan.key->pressed()) {
			ExplosionSystem::makeExplosion(scene, Entity(scene, entity));
		}
	}
}

}