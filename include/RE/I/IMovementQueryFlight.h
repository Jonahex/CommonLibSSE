#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementQueryFlight : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryFlight;

		~IMovementQueryFlight() override;  // 00
	};
	static_assert(sizeof(IMovementQueryFlight) == 0x8);
}
