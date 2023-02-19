#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class BSPSysLODModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysLODModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysLODModifier;

		~BSPSysLODModifier() override;  // 00

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
		float lodBeginDistance;  // 30
		float lodEndDistance;    // 34
		float endEmitScale;      // 38
		float endSize;           // 3C
	};
	static_assert(sizeof(BSPSysLODModifier) == 0x40);
}
