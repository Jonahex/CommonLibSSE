#pragma once

#include "RE/N/NiPSysModifier.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BSPSysInheritVelocityModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysInheritVelocityModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysInheritVelocityModifier;

		~BSPSysInheritVelocityModifier() override;  // 00

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
		void          HandleReset() override;                                                                                                    // 27
		
		// members
		NiNode*  target;                 // 30
		NiPoint3 lastUpdateTranslation;  // 38
		NiPoint3 calculatedVelocity;     // 44
		float    lastUpdateTime;         // 50
		float    inheritProbability;     // 54
		float    velocityMultiplier;     // 58
		float    velocityVariation;      // 5C
	};
	static_assert(sizeof(BSPSysInheritVelocityModifier) == 0x60);
}
