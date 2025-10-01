#include <archimedes/Engine.h>
#include <VulkanVs.h>

int main() {
	arch::Logger::init(arch::LogLevel::debug);

	arch::Unique<arch::Application> application = arch::createUnique<vs::VulkanVs>();

	auto engineConfig = arch::EngineConfig {
		.windowWidth = 1600,
		.windowHeight = 900,
		.windowTitle = "VulkanVs",
		.backgroundColor = arch::Color(0,0,0,0),
		.renderingApi = arch::gfx::RenderingAPI::Nvrhi_VK
	};

	auto engine = arch::Engine(engineConfig, application);
	engine.start();
}