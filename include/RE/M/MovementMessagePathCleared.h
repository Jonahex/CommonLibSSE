#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	class BSPathingSolution;

	class MovementMessagePathCleared : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathCleared;

		~MovementMessagePathCleared() override;  // 00

		// override (MovementMessagePathEvent)
		uint32_t GetNameHash() override;  // 01

		// members
		BSTSmartPointer<BSPathingSolution> pathingSolution;  // 18
	};
	static_assert(sizeof(MovementMessagePathCleared) == 0x20);
}
