#pragma once

#include <archimedes/Application.h>
#include <archimedes/physics/System.h>
#include <archimedes/Ref.h>

using namespace arch;

namespace vs {

class VulkanVs: public Application {
public:
	VulkanVs() noexcept = default;

	void init() noexcept override;
	void update() noexcept override;

private:
	Ref<physics::System> _physicsSystem;
};

}
