#pragma once

#include <random>
#include <archimedes/Mmath.h>
#include <archimedes/Input.h>
#include <archimedes/gfx/Texture.h>
#include <archimedes/gfx/pipeline/Pipeline.h>
#include <archimedes/asset/mesh/Mesh.h>

using namespace arch;

namespace vs {

struct Wulkan {
	using FloatDist = std::uniform_real_distribution<float>;

	u32 particleCount;
	input::Key* key;

	FloatDist explosionAngleDist;
	FloatDist velocityDist;
	FloatDist rotationSpeedDist;
	FloatDist sizeDist;
	FloatDist eDist;

	Ref<gfx::Texture> texture;
	Ref<gfx::pipeline::Pipeline> particlePipeline;
	Ref<asset::mesh::Mesh> particleMesh;

	float3 particleOrigin;

	bool isRight;
};

}