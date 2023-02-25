#pragma once

#include "RE/N/NiColor.h"
#include "RE/N/NiPSysCollider.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class NiAVObject;

	class NiPSysPlanarCollider : public NiPSysCollider
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysPlanarCollider;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysPlanarCollider;

		~NiPSysPlanarCollider() override;  // 00

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
		float       width;           // 48
		float       height;          // 4C
		NiPoint3    xAxis;           // 50
		NiPoint3    yAxis;           // 5C
		float       unk68;           // 68
		float       unk6C;           // 6C
		NiColorA    unk70;           // 70
		NiPoint3    unk80;           // 80
		NiPoint3    unk8C;           // 8C
		NiPoint3    unk98;           // 98
		NiPoint3    unkA4;           // A4
		NiTransform unkB0;           // B0
		NiTransform unkE4;           // E4
	};
	static_assert(sizeof(NiPSysPlanarCollider) == 0x118);
}
