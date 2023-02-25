#pragma once

#include "RE/N/NiObject.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiColorA;
	class NiPSysColliderManager;
	class NiPSysData;
	class NiPSysSpawnModifier;

	class NiPSysCollider : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysCollider;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysCollider;

		~NiPSysCollider() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D

		// add
		virtual NiPSysCollider* Update(NiPoint3* position, float* time, NiPSysData* particleData, uint16_t particleIndex, NiPoint3* position01) = 0;                            // 25
		virtual void            AddOrRemoveParticle(void* unk00, NiPSysData* particleData, uint16_t particleIndex, NiPoint3* positions, NiPoint3* radii, NiColorA* rotations);  // 26
		virtual void            UpdateTransforms() = 0;                                                                                                                         // 27

		// members
		float                     bounce;          // 10
		bool                      spawnOnCollide;  // 14
		bool                      dieOnCollide;    // 15
		NiPSysSpawnModifier*      spawnModifier;   // 18
		NiPoint3                  unk20;           // 20
		float                     unk2c;           // 2C
		NiPSysColliderManager*    parent;          // 30
		NiPointer<NiPSysCollider> nextCollider;    // 38
	};
	static_assert(sizeof(NiPSysCollider) == 0x40);
}
