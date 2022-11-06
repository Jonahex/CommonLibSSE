#pragma once

#include "RE/H/hkbCharacterDataCharacterControllerInfo.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbCharacterStringData;
	class hkbFootIkDriverInfo;
	class hkbHandIkDriverInfo;
	class hkbMirroredSkeletonInfo;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	class hkbCharacterData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterData;

		~hkbCharacterData() override;  // 00

		hkbCharacterDataCharacterControllerInfo m_characterControllerInfo;	// 10
		hkVector4                               m_modelUpMS;				// 30
		hkVector4                               m_modelForwardMS;			// 40
		hkVector4                               m_modelRightMS;				// 50
		hkArray<hkbVariableInfo>                m_characterPropertyInfos;	// 60
		hkArray<std::int32_t>                   m_numBonesPerLod;			// 70
		hkRefPtr<hkbVariableValueSet>           m_characterPropertyValues;	// 80
		hkRefPtr<hkbFootIkDriverInfo>           m_footIkDriverInfo;			// 88
		hkRefPtr<hkbHandIkDriverInfo>           m_handIkDriverInfo;			// 90
		hkRefPtr<hkbCharacterStringData>        m_stringData;				// 98
		hkRefPtr<hkbMirroredSkeletonInfo>       m_mirroredSkeletonInfo;		// A0
		float									m_scale;					// A8
		std::int16_t                            m_numHands;					// AC
		std::int16_t                            m_numFloatSlots;			// AE
	};
	static_assert(sizeof(hkbCharacterData) == 0xB0);
}
