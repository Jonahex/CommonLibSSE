#pragma once

#include "RE/N/NiSingleInterpController.h"

namespace RE
{
	class NiPSysModifier;

	class NiPSysModifierCtlr : public NiSingleInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysModifierCtlr;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysModifierCtlr;

		~NiPSysModifierCtlr() override;  // 00

		// override (NiSingleInterpContoller)
		const NiRTTI*   GetRTTI() const override;                                                         // 02
		void            LoadBinary(NiStream& a_stream) override;                                          // 18
		void            LinkObject(NiStream& a_stream) override;                                          // 19
		bool            RegisterStreamables(NiStream& a_stream) override;                                 // 1A
		void            SaveBinary(NiStream& a_stream) override;                                          // 1B
		bool            IsEqual(NiObject* a_object) override;                                             // 1C
		void            ProcessClone(NiCloningProcess& a_cloning) override;                               // 1D
		void            PostLinkObject([[maybe_unused]] NiStream& a_stream) override;                     // 1E
		void            SetTarget(NiObjectNET* a_target) override;                                        // 28
		const char*     GetCtlrID() override;                                                             // 36
		bool            IsValidInterpolatorTarget(NiObject* a_object) const override;                     // 3C

		// add
		virtual void Unk3D() const;  // 3D - { return; }

		// members
		BSFixedString   modifierName;    // 50
		NiPSysModifier* targetModifier;  // 58
	};
	static_assert(sizeof(NiPSysModifierCtlr) == 0x60);
}
