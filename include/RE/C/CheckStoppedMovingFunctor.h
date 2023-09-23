#pragma once

#include "RE/I/ICheckEndReachedFunctor.h"

namespace RE
{
	class CheckStoppedMovingFunctor : public ICheckEndReachedFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_CheckStoppedMovingFunctor;

		~CheckStoppedMovingFunctor() override;  // 00

		// override (ICheckEndReachedFunctor)
		bool     Check(const IPathFollowerState::Context& context) override;  // 01
	};
	static_assert(sizeof(CheckStoppedMovingFunctor) == 0x08);
}
