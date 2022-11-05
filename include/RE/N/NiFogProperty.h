#pragma once

#include "RE/N/NiColor.h"
#include "RE/N/NiProperty.h"

namespace RE
{
	class NiFogProperty : public NiProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiFogProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiFogProperty;

		~NiFogProperty() override;  // 00

		// override (NiProperty)
		const NiRTTI*      GetRTTI() const override;                           // 02
		NiObject*          CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void               LoadBinary(NiStream& a_stream) override;            // 18
		void               LinkObject(NiStream& a_stream) override;            // 19 - { NiProperty::LinkObject(a_stream); }
		bool               RegisterStreamables(NiStream& a_stream) override;   // 1A - { return NiProperty::RegisterStreamables(a_stream); }
		void               SaveBinary(NiStream& a_stream) override;            // 1B
		bool               IsEqual(NiObject* a_object) override;               // 1C
		[[nodiscard]] Type GetType() const override;                           // 25 - { return Type::kFog; }

		// members
		std::uint32_t flags;           // 30
		float         fogDepth;        // 34
		NiColor       fogColor;        // 38
		NiColor       unk44;           // 44
	};
	static_assert(sizeof(NiFogProperty) == 0x50);
}
