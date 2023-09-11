#pragma once

#include "RE/M/MovementMessage.h"
#include "RE/P/PathingPoint.h"

namespace RE
{
	class MovementMessageBlocked : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageBlocked;

		~MovementMessageBlocked() override;  // 00

		// override (MovementMessage)
		uint32_t GetNameHash() override;                             // 01
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 03
		void     Unk04(void*) override;                              // 04
	};
	static_assert(sizeof(MovementMessageBlocked) == 0x10);
}
