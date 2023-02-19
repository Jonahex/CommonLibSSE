#pragma once

#include "RE/N/NiPSysFieldModifier.h"

namespace RE
{
	class NiPSysTurbulenceFieldModifier : public NiPSysFieldModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysTurbulenceFieldModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysTurbulenceFieldModifier;

		~NiPSysTurbulenceFieldModifier() override;  // 00

		// override (NiPSysFieldModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                        // 1D
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25

		// members
		float frequency;       // 50
		float invFrequency;    // 54
		float lastUpdateTime;  // 58
	};
	static_assert(sizeof(NiPSysTurbulenceFieldModifier) == 0x60);
}
