#pragma once

#include "RE/M/MovementMessageDoor.h"

namespace RE
{
	class MovementMessageApproachingDoor : public MovementMessageDoor
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageApproachingDoor;

		~MovementMessageApproachingDoor() override;  // 00

		// override (MovementMessageDoor)
		uint32_t GetNameHash() override;  // 01
	};
	static_assert(sizeof(MovementMessageApproachingDoor) == 0x18);
}
