#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/M/MovementMessage.h"

namespace RE
{
	class MovementMessageActorCollision : public MovementMessage
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessageActorCollision;

		~MovementMessageActorCollision() override;  // 00

		// override (MovementMessage)
		uint32_t GetNameHash() override;                             // 01
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 02
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 03
		void     Unk04(void*) override;                              // 04

		// members
		ActorHandle actorHandle;  // 10
	};
	static_assert(sizeof(MovementMessageActorCollision) == 0x18);
}
