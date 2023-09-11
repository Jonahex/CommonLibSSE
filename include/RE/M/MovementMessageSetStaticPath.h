#pragma once

#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageSetStaticPath : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageSetStaticPath;

		~MovementMessageSetStaticPath() override;  // 00

		// override (MovementMessage)
		uint32_t GetNameHash() override;                             // 01
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 03

		// members
		bool isStaticPath;  // 10
	};
	static_assert(sizeof(MovementMessageSetStaticPath) == 0x18);
}
