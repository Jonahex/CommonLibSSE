#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkpCharacterControllerCinfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpCharacterControllerCinfo;

		~hkpCharacterControllerCinfo() override;  // 00
	};
	static_assert(sizeof(hkpCharacterControllerCinfo) == 0x10);
}
