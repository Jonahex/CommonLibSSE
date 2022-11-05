#pragma once

#include "RE/N/NiFogProperty.h"
#include "RE/N/NiPlane.h"

namespace RE
{
	class BSFogProperty : public NiFogProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSFogProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSFogProperty;

		~BSFogProperty() override;  // 00

		// override (NiFogProperty)
		const NiRTTI*      GetRTTI() const override;                           // 02
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;  // 17

		// members
		float         unk50;	// 50
		float         unk54;	// 54
		uint64_t      unk58;	// 58
		NiPlane       unk60;	// 60
		uint64_t      unk70;	// 70
		uint64_t      unk78;	// 78
		float         unk80;	// 80
		float         pad84;	// 84
		float         unk88;	// 88
		float         pad8C;    // 8C
	};
	static_assert(sizeof(BSFogProperty) == 0x90);
}
