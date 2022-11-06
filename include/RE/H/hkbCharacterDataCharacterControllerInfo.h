#pragma once

#include "RE/H/hkRefPtr.h"

namespace RE
{
	class hkpCharacterControllerCinfo;

	class hkbCharacterDataCharacterControllerInfo
	{
	public:
		float									m_capsuleHeight;			// 00
		float									m_capsuleRadius;			// 04
		std::uint32_t                           m_collisionFilterInfo;		// 08
		hkRefPtr<hkpCharacterControllerCinfo>	m_characterControllerCinfo;	// 10
	};
	static_assert(sizeof(hkbCharacterDataCharacterControllerInfo) == 0x18);
}
