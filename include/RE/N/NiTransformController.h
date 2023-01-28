#pragma once

#include "RE/N/NiSingleInterpController.h"

namespace RE
{
	class NiTransformController : public NiSingleInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiTransformController;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiTransformController;

		~NiTransformController() override;  // 00

		// override (NiSingleInterpController)
		const NiRTTI*        GetRTTI() const override;                                                                                                                                                 // 02
		NiObject*            CreateClone(NiCloningProcess& a_cloning) override;                                                                                                                        // 17
		void                 LoadBinary(NiStream& a_stream) override;                                                                                                                                  // 18
		void                 LinkObject(NiStream& a_stream) override;                                                                                                                                  // 19
		bool                 RegisterStreamables(NiStream& a_stream) override;                                                                                                                         // 1A
		void                 SaveBinary(NiStream& a_stream) override;                                                                                                                                  // 1B
		bool                 IsEqual(NiObject* a_object) override;                                                                                                                                     // 1C
		void                 Update(float a_time) override;                                                                                                                                            // 27
		bool                 IsTransformController() const override;                                                                                                                                   // 29
		NiInterpolator*      CreatePoseInterpolator(std::uint16_t a_index) override;                                                                                                                   // 37
		void                 SynchronizePoseInterpolator(NiInterpolator* a_interp, std::uint16_t a_index) override;                                                                                    // 38
		NiBlendInterpolator* CreateBlendInterpolator(std::uint16_t a_index, bool a_managerControlled, bool a_accumulateAnimations, float a_weightThreshold, std::uint8_t a_arraySize) const override;  // 39
		bool                 InterpolatorIsCorrectType(NiInterpolator* a_interpolator, std::uint16_t a_index) const override;                                                                          // 3B
		bool                 IsValidInterpolatorTarget(NiObject* a_object) const override;                                                                                                             // 3C
	};
	static_assert(sizeof(NiTransformController) == 0x50);
}
