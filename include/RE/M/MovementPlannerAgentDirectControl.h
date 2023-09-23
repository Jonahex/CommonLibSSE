#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementPlannerAgent.h"
#include "RE/M/MovementVector.h"

namespace RE
{
	class MovementControllerAI;

	class MovementPlannerAgentDirectControl :
		public MovementPlannerAgent  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPlannerAgentDirectControl;

		~MovementPlannerAgentDirectControl() override;  // 00

		// override (MovementAgent)
		const BSFixedString& GetName() const override;                                          // 01
		MovementAgentType    GetType() override;                                                // 02
		void                 SetMovementController(MovementControllerAI* controller) override;  // 04
		void                 RemoveMovementController() override;                               // 0A

		// override (IMovementPlannerAgent)
		const BSFixedString& GetPlannerAgentName() override;                                    // 01
		void                 PlanMovement(float* deltaTime, PlannerContext& context) override;  // 02
		void                 PlanMovementVirtual(float* deltaTime, bool&) override;             // 03

		// members
		MovementControllerAI* controller;            // 20
		BSReadWriteLock       lock;                  // 28
		MovementVector        directMovementVector;  // 30
		NiPoint3              directAngle;           // 40
	};
	static_assert(sizeof(MovementPlannerAgentDirectControl) == 0x50);
}
