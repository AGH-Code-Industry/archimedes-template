#include "LayerMatrix.h"

namespace vs::coll {

consteval bool layerMatrix(u32 l1, u32 l2) {
	auto matrix = layerMatrix();
	if (l1 > l2) {
		std::swap(l1, l2);
	}
	if (l1 < matrix.size() && l2 < matrix[l1].size()) {
		return *(matrix[l1].rbegin() + l2 - l1);
	}
	return false;
}

consteval u32 layerCount() {
	return layerMatrix().size();
}

}