#pragma once

#include "RE/I/IPathFollowerAction.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageJump 
		: public MovementMessage  // 001
		, public IPathFollowerAction  // 002
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageJump;

		~MovementMessageJump() override;  // 00

		// override (MovementMessage)
		uint32_t             GetNameHash() override;                             // 01
		void                 OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void                 OnLoadGame(BSPathingStreamRead* stream) override;   // 03
		IPathFollowerAction* GetPathFollowerAction() override;                   // 05

		// members
		float jumpHeight;  // 18
	};
	static_assert(sizeof(MovementMessageJump) == 0x20);
}
