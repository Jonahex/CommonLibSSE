#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class BSTableCurve;

	class BSPSysScaleModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysScaleModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysScaleModifier;

		~BSPSysScaleModifier() override;  // 00

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
		NiPointer<BSTableCurve> scale;
	};
	static_assert(sizeof(BSPSysScaleModifier) == 0x38);
}
