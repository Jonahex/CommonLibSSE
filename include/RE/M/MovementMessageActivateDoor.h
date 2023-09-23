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

		// override (IPathFollowerAction)
		bool OnStartSlowingDown(IPathFollowerState::Context& context, float pathParameter, float& outPathParameter) override;  // 01
		bool OnStopSlowingDown(IPathFollowerState::Context& context, float& outPathSpeed) override;                            // 02
		bool OnStopMovingAlongPath(IPathFollowerState::Context& context, float& outPathParameter) override;                    // 03
	};
	static_assert(sizeof(MovementMessageActivateDoor) == 0x18);
}
