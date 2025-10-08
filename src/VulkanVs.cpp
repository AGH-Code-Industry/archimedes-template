#include <VulkanVs.h>
#include <MakeTexture.h>
#include <LayerMatrixDef.h>
#include <systems/colliders/LayerSystem.h>
#include <archimedes/Font.h>
#include <archimedes/Scene.h>
#include <systems/Wulkan.h>
#include <systems/Ground.h>
#include <systems/Competition.h>
#include <systems/colliders/AABBSystem.h>
#include <systems/Particle.h>
#include <components/Particle.h>
#include <components/colliders/LayeredAABB.h>
#include <systems/Explosion.h>
#include <systems/Kill.h>
#include <Config.h>

namespace vs {

void VulkanVs::init() noexcept {
	font::FontDB::get()["Arial"]->bold()->assure();

	Ref<Scene> scene = createRef<Scene>();
	scene::SceneManager::get()->changeScene(scene);

	_physicsSystem = createUnique<physics::System>(scene->domain());

	WulkanSystem::setup(scene->newEntity(), input::Keyboard::shiftLeft, false);
	WulkanSystem::setup(scene->newEntity(), input::Keyboard::shiftRight, true);

	GroundSystem::setup(*scene);

	CompetitionSystem::setup(*scene);
}

void VulkanVs::update() noexcept {
	Ref<Scene> scene = scene::SceneManager::get()->currentScene();

	coll::AABBSystem::prePhysicsFetch(scene->domain());
	_physicsSystem->update();
	coll::AABBSystem::postPhysicsUpdate(scene->domain());

	coll::LayerSystem::update(scene->domain());
	ParticleSystem::update(scene->domain());
	ExplosionSystem::updateText(scene->domain());

	KillSystem::update(*scene);

	WulkanSystem::update(*scene);
	CompetitionSystem::update(*scene);
}

}