#pragma once

#include "RE/N/NiPSysModifierBoolCtlr.h"

namespace RE
{
	class NiPSysModifierActiveCtlr : public NiPSysModifierBoolCtlr
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysModifierActiveCtlr;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysModifierActiveCtlr;

		~NiPSysModifierActiveCtlr() override;  // 00

		// override (NiPSysModifierBoolCtlr)
		const NiRTTI* GetRTTI() const override;                                            // 02
		NiObject*     CreateClone([[maybe_unused]] NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;                             // 18
		void          LinkObject(NiStream& a_stream) override;                             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                    // 1A
		void          SaveBinary(NiStream& a_stream) override;                             // 1B
		bool          IsEqual(NiObject* a_object) override;                                // 1C
		bool          IsValidInterpolatorTarget(NiObject* a_object) const override;        // 3C
		void          GetControlledValue(bool& value) const override;                      // 3E
		void          SetControlledValue(bool value) override;                             // 3F
	};
	static_assert(sizeof(NiPSysModifierActiveCtlr) == 0x60);
}
