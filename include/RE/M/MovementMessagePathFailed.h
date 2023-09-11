#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	class BSPathingSolution;

	class MovementMessagePathFailed : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathFailed;

		~MovementMessagePathFailed() override;  // 00

		// override (MovementMessagePathEvent)
		uint32_t GetNameHash() override;  // 01

		// members
		BSTSmartPointer<BSPathingSolution> pathingSolution;  // 18
	};
	static_assert(sizeof(MovementMessagePathFailed) == 0x20);
}
