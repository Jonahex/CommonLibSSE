#pragma once

#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbWorldFromModelModeData
	{
	public:
		enum class WorldFromModelMode
		{
			UseOld = 0,
			UseInput = 1,
			Compute = 2,
			None = 3,
			Ragdoll = 4,
		};

		std::int16_t                                      poseMatchingBone0;  // 00
		std::int16_t                                      poseMatchingBone1;  // 02
		std::int16_t                                      poseMatchingBone2;  // 04
		stl::enumeration<WorldFromModelMode, std::int8_t> mode;               // 06
	};
	static_assert(sizeof(hkbWorldFromModelModeData) == 0x8);
}
