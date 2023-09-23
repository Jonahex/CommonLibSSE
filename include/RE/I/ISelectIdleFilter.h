#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	struct IdleAnimationData;

	class ISelectIdleFilter
	{
	public:
		inline static constexpr auto RTTI = RTTI_ISelectIdleFilter;

		virtual ~ISelectIdleFilter();  // 00

		// add
		virtual uint32_t FilterIdle(const BSScrapArray<IdleAnimationData>) = 0;  // 01                                                                                                      // 05
	};
	static_assert(sizeof(ISelectIdleFilter) == 0x8);
}
