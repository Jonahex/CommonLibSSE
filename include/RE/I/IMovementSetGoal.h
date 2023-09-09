#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	class BSPathingRequest;
	class BSPathingSolution;

	class IMovementSetGoal : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSetGoal;

		~IMovementSetGoal() override;  // 00

		// add
		virtual void SetGoal(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;                                                                        // 01
		virtual void SetGoalAndSolution(const BSTSmartPointer<BSPathingSolution>& pathingSolution, const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;  // 02
		virtual void ResetGoal() = 0;                                                                                                                             // 03
		virtual void RestartGoal() = 0;                                                                                                                           // 04
	};
	static_assert(sizeof(IMovementSetGoal) == 0x8);
}
