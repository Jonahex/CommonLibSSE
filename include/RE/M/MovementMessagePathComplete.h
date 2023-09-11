#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	class BSPathingSolution;

	class MovementMessagePathComplete : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathComplete;

		~MovementMessagePathComplete() override;  // 00

		// override (MovementMessagePathEvent)
		uint32_t GetNameHash() override;  // 01

		// members
		BSTSmartPointer<BSPathingSolution> pathingSolution;  // 18
	};
	static_assert(sizeof(MovementMessagePathComplete) == 0x20);
}
