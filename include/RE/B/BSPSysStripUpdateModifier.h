#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class BSPSysStripUpdateModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysStripUpdateModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysStripUpdateModifier;

		~BSPSysStripUpdateModifier() override;  // 00

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

		// members
		float updateDeltaTime;  // 30
	};
	static_assert(sizeof(BSPSysStripUpdateModifier) == 0x38);
}
