#pragma once

#include "RE/P/PathingPoint.h"

namespace RE
{
	struct WarpPoint : PathingPoint
	{
		NiPoint3 angle;         // 30
		uint32_t messageIndex;  // 3C
	};
	static_assert(sizeof(WarpPoint) == 0x40);
}
