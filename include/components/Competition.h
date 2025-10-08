#pragma once

namespace vs {

template<bool IsRight>
struct CompetitionMaxTextFlag {
	static constexpr bool flagComponent = true;
};

template<bool IsRight>
struct CompetitionCurrentTextFlag {
	static constexpr bool flagComponent = true;
};

}