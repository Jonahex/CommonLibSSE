#pragma once

#include "RE/I/IPathFollowerAction.h"
#include "RE/M/MovementMessageDoor.h"

namespace RE
{
	class MovementMessageActivateDoor 
		: public MovementMessageDoor // 001
		, public IPathFollowerAction // 002
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageActivateDoor;

		~MovementMessageActivateDoor() override;  // 00

		// override (MovementMessageDoor)
		uint32_t             GetNameHash() override;            // 01
		IPathFollowerAction* GetPathFollowerAction() override;  // 05
	};
	static_assert(sizeof(MovementMessageActivateDoor) == 0x18);
}
