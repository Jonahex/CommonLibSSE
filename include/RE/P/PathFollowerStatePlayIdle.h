#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/I/IdleAnimationData.h"
#include "RE/I/IPathFollowerState.h"
#include "RE/T/Tweener.h"

namespace RE
{
	class PathFollowerStatePlayIdle : public IPathFollowerState
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathFollowerStatePlayIdle;

		class IdleData : public BSIntrusiveRefCounted
		{
			Tweener           tweener;            // 00
			IdleAnimationData idleAnimationData;  // 88
		};
		static_assert(sizeof(IdleData) == 0xF8);

		enum class State
		{
			IdleNotStarted = 0x0,
			IdleStarted = 0x1,
			IdleFinished = 0x2,
		};

		~PathFollowerStatePlayIdle() override;  // 00

		// override (IPathFollowerState)
		bool PlanMovement(Context* context, IMovementPlannerAgent::PlannerContext& plannerContext) override;         // 01
		void OnSaveGame(BSPathingStreamWrite& stream, ICheckEndReachedFunctorMapper* functorMapper) const override;  // 02
		void OnLoadGame(BSPathingStreamRead& stream, ICheckEndReachedFunctorMapper* functorMapper) override;         // 03

		BSTSmartPointer<IdleData>        idleData;  // 08
		stl::enumeration<State, int32_t> state;     // 10
	};
	static_assert(sizeof(PathFollowerStatePlayIdle) == 0x18);
}
