#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbStateChooser : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateChooser;

		~hkbStateChooser() override;  // 00
	};
	static_assert(sizeof(hkbStateChooser) == 0x10);
}
