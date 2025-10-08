#pragma once

#include <chrono>

namespace vs {

struct BoomTextTime {
	decltype(std::chrono::high_resolution_clock::now()) value;
};

}