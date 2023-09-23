#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MovementMessage.h"
#include "RE/T/Tweener.h"

namespace RE
{
	class IMovementPlayIdleResult;

	class MovementMessagePlayIdle : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessagePlayIdle;

		~MovementMessagePlayIdle() override;  // 00

		// override (MovementMessage)
		uint32_t GetNameHash() override;                             // 01
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 03
		void     Unk04(void*) override;                              // 04

		// members
		BSFixedString                            eventName;       // 10
		Tweener                                  tweener;         // 18
		BSTSmartPointer<IMovementPlayIdleResult> playIdleResult;  // A0
	};
	static_assert(sizeof(MovementMessagePlayIdle) == 0xA8);
}
