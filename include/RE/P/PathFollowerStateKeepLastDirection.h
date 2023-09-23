#pragma once

#include "RE/I/IPathFollowerState.h"
#include "RE/M/MovementVector.h"

namespace RE
{
	class ICheckEndReachedFunctor;

	class PathFollowerStateKeepLastDirection : public IPathFollowerState
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathFollowerStateKeepLastDirection;

		~PathFollowerStateKeepLastDirection() override;  // 00

		// override (IPathFollowerState)
		bool PlanMovement(Context* context, IMovementPlannerAgent::PlannerContext& plannerContext) override;         // 01
		void OnSaveGame(BSPathingStreamWrite& stream, ICheckEndReachedFunctorMapper* functorMapper) const override;  // 02
		void OnLoadGame(BSPathingStreamRead& stream, ICheckEndReachedFunctorMapper* functorMapper) override;         // 03

		MovementVector           targetVector;            // 08
		ICheckEndReachedFunctor* checkEndReachedFunctor;  // 18
	};
	static_assert(sizeof(PathFollowerStateKeepLastDirection) == 0x20);
}
