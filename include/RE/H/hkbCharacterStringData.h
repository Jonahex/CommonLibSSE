#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkbCharacterStringData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterStringData;

		~hkbCharacterStringData() override;  // 00

		hkArray<hkStringPtr> m_deformableSkinNames;					// 10
		hkArray<hkStringPtr> m_rigidSkinNames;						// 20
		hkArray<hkStringPtr> m_animationNames;						// 30
		hkArray<hkStringPtr> m_animationFilenames;					// 40
		hkArray<hkStringPtr> m_characterPropertyNames;				// 50
		hkArray<hkStringPtr> m_retargetingSkeletonMapperFilenames;	// 60
		hkArray<hkStringPtr> m_lodNames;							// 70
		hkArray<hkStringPtr> m_mirroredSyncPointSubstringsA;		// 80
		hkArray<hkStringPtr> m_mirroredSyncPointSubstringsB;		// 90
		hkStringPtr          m_name;								// A0
		hkStringPtr          m_rigName;								// A8
		hkStringPtr          m_ragdollName;							// B0
		hkStringPtr          m_behaviorFilename;					// B8
	};
	static_assert(sizeof(hkbCharacterStringData) == 0xC0);
}
