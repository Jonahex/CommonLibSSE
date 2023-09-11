#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class BSPathingRequest;

	class MovementMessagePathEvent : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePathEvent;

		~MovementMessagePathEvent() override;  // 00

		// override (MovementMessage)
		void OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void OnLoadGame(BSPathingStreamRead* stream) override;   // 03
		void Unk04(void*) override;                              // 04

		// members
		BSTSmartPointer<BSPathingRequest> pathingRequest;  // 10
	};
	static_assert(sizeof(MovementMessagePathEvent) == 0x18);
}
