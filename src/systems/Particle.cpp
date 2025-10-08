#include <systems/Particle.h>
#include <components/Particle.h>
#include <Defaults.h>
#include <archimedes/physics/System.h>
#include <archimedes/physics/components/Moveable.h>
#include <components/colliders/LayerCollisionFlag.h>
#include <components/colliders/LayeredAABB.h>
#include <Config.h>
#include <components/Kill.h>

namespace vs {

void ParticleSystem::setup(Scene& scene, Entity particle, Wulkan& wulkan) {
	static auto rng = std::mt19937(std::random_device{}());
	static auto initAngleDist = std::uniform_real_distribution(0.f, 360.f);

	const float size = wulkan.sizeDist(rng);
	auto&& transform = particle.addComponent(
		scene::components::TransformComponent{
			.position = wulkan.particleOrigin + float3{0, 0, -0.1f},
			.rotation = glm::angleAxis(initAngleDist(rng), zAxis()),
			.scale = float3{size, size, 0}
		}
	);
	particle.addComponent(
		scene::components::MeshComponent{
			.mesh = wulkan.particleMesh,
			.pipeline = wulkan.particlePipeline
		}
	);

	if (wulkan.isRight) {
		particle.addComponent<Particle<true>>() = {
			.rotationQuat = glm::angleAxis(wulkan.rotationSpeedDist(rng), zAxis()),
			.e = std::sqrt(wulkan.eDist(rng))
		};
	} else {
		particle.addComponent<Particle<false>>() = {
			.rotationQuat = glm::angleAxis(wulkan.rotationSpeedDist(rng), zAxis()),
			.e = std::sqrt(wulkan.eDist(rng))
		};
	}

	const auto angle = wulkan.explosionAngleDist(rng);
	const auto vel = wulkan.velocityDist(rng);

	particle.addComponent(
		physics::Moveable{
			.center = {.mass = 1.f, .position = transform.position},
			.force = float2{0, -9.81f * 100},
			.velocity = vel * float2{-sin(angle), cos(angle)}
		}
	);
	auto&& aabb = particle.addComponent<coll::LayeredAABB<Layers::particle>>();
	aabb.topLeft = transform.position + float3{-size, size, 0} / 2.f;
	aabb.bottomRight = transform.position - float3{-size, size, 0} / 2.f;
}

inline void particleCollisions(ecs::Domain& domain);

void ParticleSystem::update(ecs::Domain& domain) {
	particleCollisions(domain);

	auto viewLeft = domain.view<scene::components::TransformComponent, const physics::Moveable, const Particle<false>>();
	auto viewRight = domain.view<scene::components::TransformComponent, const physics::Moveable, const Particle<true>>();

	for (auto&& [transform, movable, particle] : viewLeft.components()) {
		transform.position = float3{movable.center.position, -0.1f};
		transform.rotation = particle.rotationQuat * transform.rotation;
	}
	for (auto&& [transform, movable, particle] : viewRight.components()) {
		transform.position = float3{movable.center.position, -0.1f};
		transform.rotation = particle.rotationQuat * transform.rotation;
	}
}

void particleCollisions(ecs::Domain& domain) {
	std::vector<ecs::Entity> toRemoveCollision;
	for (auto&& [entity, particle, movable, aabb] : domain.view<
		Particle<false>,
		LayerCollisionFlag<Layers::ground>,
		physics::Moveable,
		coll::LayeredAABB<Layers::particle>>().all()
		) {
		++particle.collisionCounter;
		if (particle.collisionCounter >= 3) {
			domain.addComponent<Kill>(entity);
			continue;
		}

		const auto insideDist = -aabb.bottomRight.y;

		movable.velocity.x *= particle.e;
		movable.velocity.y *= -particle.e;

		aabb.topLeft.y += insideDist;
		aabb.bottomRight.y += insideDist;
		movable.center.position.y += insideDist;

		toRemoveCollision.push_back(entity);
	}
	for (auto&& [entity, particle, movable, aabb] : domain.view<
		Particle<true>,
		LayerCollisionFlag<Layers::ground>,
		physics::Moveable,
		coll::LayeredAABB<Layers::particle>>().all()
		) {
		++particle.collisionCounter;
		if (particle.collisionCounter >= 3) {
			domain.addComponent<Kill>(entity);
			continue;
		}

		const auto insideDist = -aabb.bottomRight.y;

		movable.velocity.x *= particle.e;
		movable.velocity.y *= -particle.e;

		aabb.topLeft.y += insideDist;
		aabb.bottomRight.y += insideDist;
		movable.center.position.y += insideDist;

		toRemoveCollision.push_back(entity);
	}

	for (auto&& entity : toRemoveCollision) {
		domain.removeComponent<LayerCollisionFlag<Layers::ground>>(entity);
	}
}


}