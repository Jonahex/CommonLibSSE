#pragma once

#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkaBone
	{
	public:
		hkStringPtr name;             // 00
		bool        lockTranslation;  // 08
	};
	static_assert(sizeof(hkaBone) == 0x10);
}
