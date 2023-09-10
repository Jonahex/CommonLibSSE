#pragma once

#include "RE/I/IMovementHandlerAgent.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementHandlerAgent :
		public MovementAgent,         // 000
		public IMovementHandlerAgent  // 001
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgent;

		~MovementHandlerAgent() override;  // 00

		// override (MovementAgent)
		IMovementInterface* GetInterfaceByName(BSFixedString* name) override;  // 03

		// override (IMovementHandlerAgent)
		const BSFixedString& GetHandlerAgentName() override;  // 01
	};
	static_assert(sizeof(MovementHandlerAgent) == 0x20);
}
