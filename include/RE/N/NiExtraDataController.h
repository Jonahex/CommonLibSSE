#pragma once

#include "RE/N/NiSingleInterpController.h"

namespace RE
{
	class NiExtraData;

	class NiExtraDataController : public NiSingleInterpController
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiExtraDataController;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiExtraDataController;

		~NiExtraDataController() override;  // 00

		// override (NiSingleInterpController)
		const NiRTTI*   GetRTTI() const override;                                                         // 02
		void            LoadBinary(NiStream& a_stream) override;                                          // 18
		void            LinkObject(NiStream& a_stream) override;                                          // 19
		bool            RegisterStreamables(NiStream& a_stream) override;                                 // 1A
		void            SaveBinary(NiStream& a_stream) override;                                          // 1B
		bool            IsEqual(NiObject* a_object) override;                                             // 1C
		void            ProcessClone(NiCloningProcess& a_cloning) override;                               // 1D
		void            PostLinkObject(NiStream& a_stream) override;                                      // 1E
		void            SetTarget(NiObjectNET* a_target) override;                                        // 28
		const char*     GetCtlrID();                                                                      // 36
		bool            IsValidInterpolatorTarget(NiObject* a_object) const override;                     // 3C

		// members
		BSFixedString          extraDataName;  // 50
		NiPointer<NiExtraData> target;         // 58
	};
	static_assert(sizeof(NiExtraDataController) == 0x60);
}
