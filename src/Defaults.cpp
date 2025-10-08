#include <Defaults.h>
#include <Config.h>

namespace vs {

Ref<gfx::buffer::Buffer> defaultUniformBuffer() {
	struct UBO {
		Mat4x4 projection;
	};
	static UBO ubo{
		glm::ortho(0.f, (float)windowWidth, 0.f, (float)windowHeight)
	};

	return gfx::Renderer::getCurrent()->getBufferManager()->createBuffer(gfx::buffer::BufferType::uniform, &ubo, sizeof(ubo));
}

std::vector<Vertex>& defaultVertices() {
	static std::vector<Vertex> value{
		{{0.f, 0.f, 0.f}, {0.f, 1.f}},
		{{-1.f, 0.f, 0.f}, {1.f, 1.f}},
		{{0.f, 1.f, 0.f}, {0.f, 0.f}},
		{{-1.f, 1.f, 0.f}, {1.f, 0.f}},
	};
	return value;
}

std::vector<Vertex>& defaultParticleVertices() {
	static std::vector<Vertex> value{
		{{0.5f, -0.5f, 0.f}, {0.f, 0.f}},
		{{-0.5f, -0.5f, 0.f}, {1.f, 0.f}},
		{{0.5f, 0.5f, 0.f}, {0.f, 1.f}},
		{{-0.5f, 0.5f, 0.f}, {1.f, 1.f}},
	};
	return value;
}

std::vector<u32>& defaultIndices() {
	static std::vector<u32> value{0, 1, 2, 2, 1, 3};
	return value;
}

}