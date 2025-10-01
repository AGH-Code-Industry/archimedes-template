//#define SPDLOG_USE_STD_FORMAT 1

#include <archimedes/Logger.h>
#include <archimedes/Ecs.h>
#include <archimedes/ArchMath.h>
#include <archimedes/utils/Assert.h>

using namespace arch;

struct TestComponent {
	float3 vec;

	TestComponent(float3 vec) {
		this->vec = vec;
		Logger::debug("+TestComponent: ({}, {}, {})", vec.x, vec.y, vec.z);
	}
	~TestComponent() {
		Logger::debug("-TestComponent");//
	}
};

int main() {
	Logger::init(LogLevel::debug);
	Logger::debug("elo tu arch, Debug == {}", ARCHIMEDES_DEBUG);

	ecs::Domain domain;
	domain.addComponent<TestComponent>(domain.newEntity(), float3{1, 2, 3});

	for (auto [test] : domain.view<TestComponent>().components()) {

	}
}