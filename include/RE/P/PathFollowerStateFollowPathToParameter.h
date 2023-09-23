#pragma once

#include "RE/I/IPathFollowerState.h"

namespace RE
{
	class ICheckEndReachedFunctor;

	class PathFollowerStateFollowPathToParameter : public IPathFollowerState
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathFollowerStateFollowPathToParameter;

		~PathFollowerStateFollowPathToParameter() override;  // 00

		// override (IPathFollowerState)
		bool PlanMovement(Context* context, IMovementPlannerAgent::PlannerContext& plannerContext) override;         // 01
		void OnSaveGame(BSPathingStreamWrite& stream, ICheckEndReachedFunctorMapper* functorMapper) const override;  // 02
		void OnLoadGame(BSPathingStreamRead& stream, ICheckEndReachedFunctorMapper* functorMapper) override;         // 03

		float                    targetParameter;         // 08
		float                    targetSpeed;             // 0C
		float                    endParameter;            // 10
		ICheckEndReachedFunctor* checkEndReachedFunctor;  // 18
	};
	static_assert(sizeof(PathFollowerStateFollowPathToParameter) == 0x20);
}
