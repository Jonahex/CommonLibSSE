#pragma once

#include "RE/I/InputEvent.h"

namespace RE
{
	class CharEvent : public InputEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_CharEvent;
		inline static constexpr auto VTABLE = VTABLE_CharEvent;

		~CharEvent() override;  // 00

		// members
		uint32_t keyCode;       // 18
	};
	static_assert(sizeof(CharEvent) == 0x20);
}
