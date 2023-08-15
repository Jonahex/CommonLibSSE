#pragma once

#include "RE/N/NiQuaternion.h"
#include "RE/N/NiTimeController.h"

namespace RE
{
	class BSLagBoneController : public NiTimeController
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLagBoneController;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSLagBoneController;

		~BSLagBoneController() override;  // 00

		// override (NiTimeController)
		const NiRTTI*      GetRTTI() const override;                           // 02
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void               LoadBinary(NiStream& a_stream) override;            // 18
		void               LinkObject(NiStream& a_stream) override;            // 19
		bool               RegisterStreamables(NiStream& a_stream) override;   // 1A
		void               SaveBinary(NiStream& a_stream) override;            // 1B
		bool               IsEqual(NiObject* a_object) override;               // 1C
		void               Update(float* a_time) override;                      // 27
		void               SetTarget(NiObjectNET* a_target) override;          // 28
		[[nodiscard]] bool TargetIsRequiredType() const override;              // 2E

		// members
		NiQuaternion unk48;            // 48
		NiPoint3     unk58;            // 58
		float        linearVelocity;   // 64
		float        linearRotation;   // 68
		float        maximumDistance;  // 6C
	};
	static_assert(sizeof(BSLagBoneController) == 0x70);
}
