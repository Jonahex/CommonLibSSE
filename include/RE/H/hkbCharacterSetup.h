#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkRefVariant.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkaSkeleton;
	class hkaSkeletonMapper;
	class hkbCharacterData;

	class hkbCharacterSetup : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbCharacterSetup;

		~hkbCharacterSetup() override;  // 00

		hkArray<hkaSkeletonMapper*> m_retargetingSkeletonMappers;		// 10
		hkRefPtr<hkaSkeleton>       m_animationSkeleton;				// 20
		hkRefPtr<hkaSkeletonMapper> m_ragdollToAnimationSkeletonMapper;	// 28
		hkRefPtr<hkaSkeletonMapper> m_animationToRagdollSkeletonMapper;	// 30
		hkRefVariant                m_animationBindingSet;				// 38
		hkRefPtr<hkbCharacterData>  m_data;								// 40
		hkRefVariant                m_mirroredSkeleton;					// 48
		hkRefVariant                m_characterPropertyIdMap;			// 50
	};
	static_assert(sizeof(hkbCharacterSetup) == 0x58);
}
