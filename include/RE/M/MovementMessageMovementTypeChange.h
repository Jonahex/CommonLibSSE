#pragma once

#include "RE/M/Movement.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageMovementTypeChange : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageMovementTypeChange;

		~MovementMessageMovementTypeChange() override;  // 00

		// override (MovementMessage)
		uint32_t GetNameHash() override;                             // 01
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 03

		// members
		Movement::TypeData oldType;  // 10
		Movement::TypeData newType;  // 50
	};
	static_assert(sizeof(MovementMessageMovementTypeChange) == 0x90);
}
