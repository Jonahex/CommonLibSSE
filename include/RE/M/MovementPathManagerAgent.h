#pragma once

#include "RE/I/IMovementPathManagerAgent.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementPathManagerAgent :
		public MovementAgent,             // 000
		public IMovementPathManagerAgent  // 001
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerAgent;

		~MovementPathManagerAgent() override;  // 00

		// override (MovementAgent)
		IMovementInterface* GetInterfaceByName(BSFixedString* name) override;  // 03

		// override (IMovementPathManagerAgent)
		const BSFixedString& GetPathManagerAgentName() override;                                                // 01
		void                 OnPathRestart(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;   // 04
		void                 OnPathComplete(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;  // 05
	};
	static_assert(sizeof(MovementPathManagerAgent) == 0x20);
}
