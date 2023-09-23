#pragma once

#include "RE/I/IMovementPlannerAgent.h"

namespace RE
{
	class BSPathingRequest;
	class BSPathingSolution;
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class ICheckEndReachedFunctorMapper;
	class IMovementState;
	class MovementControllerAI;

	class IPathFollowerState
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathFollowerState;

		struct Context
		{
			NiPoint3                           position;            // 00
			NiPoint3                           angle;               // 0C
			BSTSmartPointer<BSPathingRequest>  pathingRequest;      // 18
			BSTSmartPointer<BSPathingSolution> pathingSolution;     // 20
			IMovementState*                    movementState;       // 28
			MovementControllerAI*              movementController;  // 30
			NiPoint3*                          targetPathPosition;  // 38
			float                              pathParameter;       // 40
			float                              deltaTime;           // 44
		};
		static_assert(sizeof(Context) == 0x48);

		virtual ~IPathFollowerState();  // 00

		// add
		virtual bool PlanMovement(Context* context, IMovementPlannerAgent::PlannerContext& plannerContext) = 0;         // 01
		virtual void OnSaveGame(BSPathingStreamWrite& stream, ICheckEndReachedFunctorMapper* functorMapper) const = 0;  // 02
		virtual void OnLoadGame(BSPathingStreamRead& stream, ICheckEndReachedFunctorMapper* functorMapper) = 0;         // 03
	};
	static_assert(sizeof(IPathFollowerState) == 0x8);
}
