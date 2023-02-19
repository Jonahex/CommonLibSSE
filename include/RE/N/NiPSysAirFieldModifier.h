#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiPSysFieldModifier.h"

namespace RE
{
	class NiPSysAirFieldModifier : public NiPSysFieldModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysAirFieldModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysAirFieldModifier;

		~NiPSysAirFieldModifier() override;  // 00

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
		NiPoint3 unk50;            // 50
		float    lastUpdateTime;   // 5C
		NiPoint3 direction;        // 60
		NiPoint3 unk6c;            // 6C
		float    airFriction;      // 78
		float    inheritVelocity;  // 7C
		bool     inheritRotation;  // 80
		bool     componentOnly;    // 81
		bool     enableSpread;     // 82
		float    spread;           // 84
	};
	static_assert(sizeof(NiPSysAirFieldModifier) == 0x88);
}
