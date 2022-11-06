#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkQuaternion.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkaFootPlacementIkSolver;

	class hkbFootIkDriver : public hkReferencedObject
	{
	public:
		struct InternalLegData
		{
			hkVector4					groundPosition;  // 00
			hkVector4					groundNormal;    // 10
			hkaFootPlacementIkSolver*	footIkSolver;    // 20
			float						verticalError;   // 28
			bool						hitSomething;    // 2C
			bool						isPlantedMS;     // 2D
		};
		static_assert(sizeof(InternalLegData) == 0x30);

		inline static constexpr auto RTTI = RTTI_hkbFootIkDriver;

		~hkbFootIkDriver() override;  // 00

		hkArray<InternalLegData> m_internalLegData;			// 10
		hkVector4                errorOutTranslation;		// 20
		hkQuaternion             alignWithGroundRotation;	// 30
		std::uint64_t            unk40;						// 40
		bool                     m_isSetUp;                 // 48
		bool                     unk49;                     // 49
		std::uint8_t             disableFootIk;				// 4A
		std::uint8_t             unk4B;                     // 4B
		float                    deltaTime;					// 4C
	};
	static_assert(sizeof(hkbFootIkDriver) == 0x50);
}
