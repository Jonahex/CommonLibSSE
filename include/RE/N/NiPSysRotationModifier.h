#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiPSysRotationModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysRotationModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysRotationModifier;

		~NiPSysRotationModifier() override;  // 00

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
		void          Initialize(NiPSysData* a_particleData, std::uint16_t, NiPoint3*) override;                                                 // 26

		// members
		float    rotationSpeed;            // 30
		float    rotationSpeedVariation;   // 34
		float    rotationAngle;            // 38
		float    rotationAngleVariation;   // 3C
		NiPoint3 rotationAxis;             // 40
		bool     randomRotationAxis;       // 4C
		bool     randomRotationSpeedSign;  // 4D
	};
	static_assert(sizeof(NiPSysRotationModifier) == 0x50);
}
