#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	struct MovementVector
	{
		NiPoint3 angle;  // 00
		float    speed;  // 0C
	};
	static_assert(sizeof(MovementVector) == 0x10);
}
