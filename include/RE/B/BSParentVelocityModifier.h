#pragma once

#include "RE/N/NiPSysModifier.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSParentVelocityModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSParentVelocityModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSParentVelocityModifier;

		~BSParentVelocityModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25
		void          Initialize(NiPSysData* a_particleData, std::uint16_t, NiPoint3*) override;                                                 // 26
		void          HandleReset() override;                                                                                                    // 27

		// members
		float    timeDelta;              // 30
		float    lastUpdateTime;         // 34
		float    damping;                // 38
		NiPoint3 lastUpdateTranslation;  // 3C
		NiPoint3 calculatedVelocity;     // 48
	};
	static_assert(sizeof(BSParentVelocityModifier) == 0x58);
}
