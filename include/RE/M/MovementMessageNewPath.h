#pragma once

#include "RE/M/MovementMessagePathEvent.h"

namespace RE
{
	class MovementMessageNewPath : public MovementMessagePathEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageNewPath;

		~MovementMessageNewPath() override;  // 00

		// override (MovementMessagePathEvent)
		uint32_t GetNameHash() override;  // 01
	};
	static_assert(sizeof(MovementMessageNewPath) == 0x18);
}
