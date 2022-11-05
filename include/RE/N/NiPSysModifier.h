#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class NiParticleSystem;
	class NiPSysData;

	class NiPSysModifier : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysModifier;

		enum class ORDER
		{
			kKillOldParticles = 0,
			kBSLOD = 1,
			kEmitter = 1000,
			kSpawn = 2000,
			kGeneral = 3000,
			kForce = 4000,
			kCollider = 5000,
			kPosUpdate = 6000,
			kPostPosUpdate = 6500,
			kBoundUpdate = 7000,
			kBSStripUpdate = 8000
		};

		~NiPSysModifier() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C - { return false; }
		void          ProcessClone(NiCloningProcess& a_cloning) override;  // 1D

		// add
		virtual bool Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) = 0;
		virtual void Initialize(NiPSysData* a_particleData, std::uint16_t, NiPoint3*);
		virtual void HandleReset();
		virtual void SetActive(bool a_active);
		virtual void SetSystemPointer(NiParticleSystem* a_target);

		// members
		BSFixedString     name;    // 10
		ORDER             order;   // 18
		std::uint32_t     pad1C;   // 1C
		NiParticleSystem* target;  // 20
		bool              active;  // 28
		std::uint8_t      pad29;   // 29
		std::uint16_t     pad2A;   // 29
		std::uint32_t     pad2C;   // 29
	};
	static_assert(sizeof(NiPSysModifier) == 0x30);
}
