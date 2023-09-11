#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class IPathFollowerAction;

	class MovementMessage :
		public BSIntrusiveRefCounted  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementMessage;

		virtual ~MovementMessage();  // 00

		// add
		virtual uint32_t             GetNameHash() = 0;                             // 01
		virtual void                 OnSaveGame(BSPathingStreamWrite* stream) = 0;  // 02
		virtual void                 OnLoadGame(BSPathingStreamRead* stream) = 0;   // 03
		virtual void                 Unk04(void*);                                  // 04 - nonempty only in MovementMessageActivateDoor
		virtual IPathFollowerAction* GetPathFollowerAction();                       // 05
	};
	static_assert(sizeof(MovementMessage) == 0x10);
}
