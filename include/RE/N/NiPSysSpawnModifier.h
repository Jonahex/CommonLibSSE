#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiPSysSpawnModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysSpawnModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysSpawnModifier;

		~NiPSysSpawnModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25
		
		// add
		virtual void Spawn(void* unk00, NiPSysData* particleData, uint16_t particleIndex, NiParticleSystem* target, NiPoint3* position, NiColorA* rotation);  // 2A
		
		// members
		uint16_t numSpawnGenerations;  // 30
		float    spawnProbability;     // 34
		uint16_t minNumToSpawn;        // 38
		uint16_t maxNumToSpawn;        // 3A
		float    spawnSpeedVariation;  // 3C
		float    spawnDirVariation;    // 40
		float    lifeSpan;             // 44
		float    lifeSpanVariation;    // 48
	};
	static_assert(sizeof(NiPSysSpawnModifier) == 0x50);
}
