#pragma once

#include "RE/I/IMovementPlannerAgent.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementPlannerAgent :
		public MovementAgent,         // 000
		public IMovementPlannerAgent  // 001
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgent;

		~MovementPlannerAgent() override;  // 00

		// override (MovementAgent)
		IMovementInterface* GetInterfaceByName(BSFixedString* name) override;  // 03

		// override (IMovementPlannerAgent)
		const BSFixedString& GetPlannerAgentName() override;  // 01
	};
	static_assert(sizeof(MovementPlannerAgent) == 0x20);
}
