#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	struct MovementTarget
	{
		enum class Type
		{
			KeepAngle = 0x0,
			FollowFixedHeading = 0x1,
			FollowTargetHeadingAndPitch = 0x2,
			FollowTargetHeading = 0x3,
		};

		stl::enumeration<Type, int32_t> type;              // 00
		NiPoint3                        targetDirection;   // 04
		float                           heading;           // 10
		float                           headingTolerance;  // 14
	};
	static_assert(sizeof(MovementTarget) == 0x18);
}
