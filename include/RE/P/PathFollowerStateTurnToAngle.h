#pragma once

#include "RE/I/IPathFollowerState.h"
#include "RE/M/MovementTarget.h"

namespace RE
{
	class PathFollowerStateTurnToAngle : public IPathFollowerState
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathFollowerStateTurnToAngle;

		~PathFollowerStateTurnToAngle() override;  // 00

		// override (IPathFollowerState)
		bool PlanMovement(Context* context, IMovementPlannerAgent::PlannerContext& plannerContext) override;         // 01
		void OnSaveGame(BSPathingStreamWrite& stream, ICheckEndReachedFunctorMapper* functorMapper) const override;  // 02
		void OnLoadGame(BSPathingStreamRead& stream, ICheckEndReachedFunctorMapper* functorMapper) override;         // 03

		MovementTarget target;  // 08
	};
	static_assert(sizeof(PathFollowerStateTurnToAngle) == 0x20);
}
