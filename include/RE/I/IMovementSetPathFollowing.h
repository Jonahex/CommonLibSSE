#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementSetPathFollowing : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSetPathFollowing;

		enum class Result
		{
			FollowingPath = 0x0,
			PathEnded = 0x1,
			PathFailed = 0x2,
		};

		~IMovementSetPathFollowing() override;  // 00

		// add
		virtual Result SetPathFollowing(bool isFollowing) = 0; // 01
	};
	static_assert(sizeof(IMovementSetPathFollowing) == 0x8);
}
