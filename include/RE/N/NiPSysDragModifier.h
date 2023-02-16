#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiPSysDragModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysDragModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysDragModifier;

		~NiPSysDragModifier() override;  // 00

		// override (NiPSysModifier)
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
		NiAVObject* dragObject;    // 30
		NiPoint3    dragAxis;      // 38
		float       percentage;    // 44
		float       range;         // 48
		float       rangeFalloff;  // 4C
	};
	static_assert(sizeof(NiPSysDragModifier) == 0x50);
}
