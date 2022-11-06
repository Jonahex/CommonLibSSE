#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbFootIkDriverInfoLeg;

	class hkbFootIkDriverInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbFootIkDriverInfo;

		~hkbFootIkDriverInfo() override;  // 00

		hkArray<hkbFootIkDriverInfoLeg> m_legs;						// 10
		float                           m_raycastDistanceUp;		// 20
		float                           m_raycastDistanceDown;		// 24
		float                           m_originalGroundHeightMS;	// 28
		float                           m_verticalOffset;			// 2C
		std::uint32_t                   m_collisionFilterInfo;		// 30
		float                           m_forwardAlignFraction;		// 34
		float                           m_sidewaysAlignFraction;	// 38
		float                           m_sidewaysSampleWidth;		// 3C
		bool                            m_lockFeetWhenPlanted;		// 40
		bool                            m_useCharacterUpVector;		// 41
		bool                            m_isQuadrupedNarrow;		// 42
	};
	static_assert(sizeof(hkbFootIkDriverInfo) == 0x48);
}
