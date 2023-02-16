#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiPSysBoundUpdateModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysBoundUpdateModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysBoundUpdateModifier;

		~NiPSysBoundUpdateModifier() override;  // 00

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

		void SetUpdateSkip(uint16_t value)
		{
			using func_t = decltype(&NiPSysBoundUpdateModifier::SetUpdateSkip);
			REL::Relocation<func_t> func{ RELOCATION_ID(73170, 74870) };
			func(this, value);
		}

		// members
		uint16_t updateSkip;  // 30
		void*    unk38;       // 38
	};
	static_assert(sizeof(NiPSysBoundUpdateModifier) == 0x40);
}
