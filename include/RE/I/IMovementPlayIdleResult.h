#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class IMovementPlayIdleResult
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlayIdleResult;

		virtual ~IMovementPlayIdleResult();  // 00

		// add
		virtual void     OnPlayIdle(const BSFixedString& eventName, bool isIdleStarted) = 0;  // 01
		virtual void     IncRef() const;                                                      // 02
		virtual uint32_t DecRef();                                                            // 03
	};
	static_assert(sizeof(IMovementPlayIdleResult) == 0x8);
}
