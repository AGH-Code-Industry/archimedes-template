#pragma once

#include <Vertex.h>
#include <archimedes/gfx/Renderer.h>

using namespace arch;

namespace vs {

Ref<gfx::buffer::Buffer> defaultUniformBuffer();

std::vector<Vertex>& defaultVertices();

std::vector<Vertex>& defaultParticleVertices();

std::vector<u32>& defaultIndices();

constexpr float3 zAxis() {
	return float3{0, 0, 1};
}

}