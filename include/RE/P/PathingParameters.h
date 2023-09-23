#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	struct PathingParameters
	{
		enum class PathEventType
		{
			PathStart = 0x0,
			PathEnd = 0x1,
			LargeMovementDelta = 0x2,
		};

		stl::enumeration<PathEventType, int32_t> pathEventType;         // 00
		NiPoint3                                 currentMovementSpeed;  // 04
		NiPoint3                                 currentRotationSpeed;  // 10
		NiPoint3                                 desiredPosition;       // 1C
		NiPoint3                                 desiredOrientation;    // 28
		NiPoint3                                 desiredMovementSpeed;  // 34
		NiPoint3                                 desiredRotationSpeed;  // 40
	};
	static_assert(sizeof(PathingParameters) == 0x50);
}
