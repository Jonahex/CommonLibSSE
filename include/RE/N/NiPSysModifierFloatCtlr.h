#pragma once

#include "RE/N/NiPSysModifierCtlr.h"

namespace RE
{
	class NiPSysModifierFloatCtlr : public NiPSysModifierCtlr
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysModifierFloatCtlr;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysModifierFloatCtlr;

		~NiPSysModifierFloatCtlr() override;  // 00

		// override (NiPSysModifierCtlr)
		const NiRTTI*        GetRTTI() const override;                                                                                                                                                 // 02
		void                 LoadBinary(NiStream& a_stream) override;                                                                                                                                  // 18
		void                 LinkObject(NiStream& a_stream) override;                                                                                                                                  // 19
		bool                 RegisterStreamables(NiStream& a_stream) override;                                                                                                                         // 1A
		void                 SaveBinary(NiStream& a_stream) override;                                                                                                                                  // 1B
		bool                 IsEqual(NiObject* a_object) override;                                                                                                                                     // 1C
		void                 Update(float a_time) override;                                                                                                                                            // 27
		NiInterpolator*      CreatePoseInterpolator(std::uint16_t a_index) override;                                                                                                                   // 37
		void                 SynchronizePoseInterpolator(NiInterpolator* a_interp, std::uint16_t a_index) override;                                                                                    // 38
		NiBlendInterpolator* CreateBlendInterpolator(std::uint16_t a_index, bool a_managerControlled, bool a_accumulateAnimations, float a_weightThreshold, std::uint8_t a_arraySize) const override;  // 39
		bool                 InterpolatorIsCorrectType(NiInterpolator* a_interpolator, std::uint16_t a_index) const override;                                                                          // 3B

		// add
		virtual void GetControlledValue(float& value) const = 0;  // 3E
		virtual void SetControlledValue(float value) = 0;         // 3F
	};
	static_assert(sizeof(NiPSysModifierFloatCtlr) == 0x60);
}
