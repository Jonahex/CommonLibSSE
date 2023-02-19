#pragma once

#include "RE/N/NiColor.h"
#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class BSPSysSimpleColorModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysSimpleColorModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysSimpleColorModifier;

		~BSPSysSimpleColorModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25
		void          SetSystemPointer(NiParticleSystem* a_target) override;                                                                     // 29

		// members
		NiColorA colors[3];           // 30
		float    fadeInPercent;       // 60
		float    fadeOutPercent;      // 64
		float    color1EndPercent;    // 68
		float    color1StartPercent;  // 6C
		float    color2EndPercent;    // 70
		float    color2StartPercent;  // 74
		bool     isMeshParticle;      // 78
	};
	static_assert(sizeof(BSPSysSimpleColorModifier) == 0x80);
}
