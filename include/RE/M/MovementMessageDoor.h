#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class BSPathingDoor;

	class MovementMessageDoor : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageDoor;

		~MovementMessageDoor() override;  // 00

		// override (MovementMessage)
		void OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void OnLoadGame(BSPathingStreamRead* stream) override;   // 03
		void Unk04(void*) override;                              // 04

		// members
		BSTSmartPointer<BSPathingDoor> pathingDoor;  // 10
	};
	static_assert(sizeof(MovementMessageDoor) == 0x18);
}
