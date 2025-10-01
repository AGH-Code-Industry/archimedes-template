#pragma once

#include <archimedes/Application.h>

namespace vs {

class VulkanVs : public arch::Application {
public:
	VulkanVs() noexcept;

	void init() noexcept override;
	void update() noexcept override;
};

}
