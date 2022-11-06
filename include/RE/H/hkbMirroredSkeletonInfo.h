#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbMirroredSkeletonInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbMirroredSkeletonInfo;

		~hkbMirroredSkeletonInfo() override;  // 00

		hkVector4				m_mirrorAxis;	// 10
		hkArray<std::uint16_t>	m_bonePairMap;	// 20
	};
	static_assert(sizeof(hkbMirroredSkeletonInfo) == 0x30);
}
