#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiColorData;

	class NiPSysColorModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysColorModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysColorModifier;

		~NiPSysColorModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25

		// members
		NiPointer<NiColorData> colorData;  // 30
		float                  startTime;  // 38
		float                  endTime;    // 3C
	};
	static_assert(sizeof(NiPSysColorModifier) == 0x40);
}
