#pragma once

#include "RE/N/NiPSysCollider.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class NiAVObject;

	class NiPSysSphericalCollider : public NiPSysCollider
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysSphericalCollider;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysSphericalCollider;

		~NiPSysSphericalCollider() override;  // 00

		// override (NiPSysCollder)
		const NiRTTI*   GetRTTI() const override;                                                                                                                       // 02
		void            LoadBinary(NiStream& a_stream) override;                                                                                                        // 18
		void            LinkObject(NiStream& a_stream) override;                                                                                                        // 19
		bool            RegisterStreamables(NiStream& a_stream) override;                                                                                               // 1A
		void            SaveBinary(NiStream& a_stream) override;                                                                                                        // 1B
		bool            IsEqual(NiObject* a_object) override;                                                                                                           // 1C
		void            ProcessClone(NiCloningProcess& a_cloning) override;                                                                                             // 1D
		NiPSysCollider* Update(NiPoint3* position, float* time, NiPSysData* particleData, uint16_t particleIndex, NiPoint3* position01) override;                       // 25
		void            AddOrRemoveParticle(void* unk00, NiPSysData* particleData, uint16_t particleIndex, NiPoint3* positions, NiPoint3* radii, NiColorA* rotations);  // 26
		void            UpdateTransforms() override;                                                                                                                    // 27

		// members
		NiAVObject* colliderObject;  // 40
		float       radius;          // 48
		float       unk4c;           // 4C
		float       unk50;           // 50
		NiPoint3    unk54;           // 54
		NiTransform unk60;           // 60
		NiTransform unk94;           // 94
	};
	static_assert(sizeof(NiPSysSphericalCollider) == 0xC8);
}
