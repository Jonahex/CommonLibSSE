#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	struct MovementData
	{
		NiPoint3 angle;          // 00
		float    speed;          // 0C
		NiPoint3 rotationSpeed;  // 10
	};
	static_assert(sizeof(MovementData) == 0x1C);
}
