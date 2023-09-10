#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IMovementPlannerSetArbitration.h"
#include "RE/M/MovementArbiter.h"

namespace RE
{
	class IMovementPlannerAgent;
	class MovementControllerAI;

	class MovementPlannerArbiter :
		public MovementArbiter,                // 000
		public IMovementPlannerSetArbitration  // 001
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerArbiter;

		~MovementPlannerArbiter() override;  // 00

		// override (MovementArbiter)
		const BSFixedString& GetPipelineStageName() const override;                                 // 01
		const BSFixedString& GetArbiterName() const override;                                       // 02
		MovementArbiterType  GetType() override;                                                    // 03
		void                 SetMovementController(MovementControllerAI* controller) override;      // 04
		void                 Activate() override;                                                   // 06
		void                 SetProcessingOrder(BSPathingStreamSimpleBufferRead* buffer) override;  // 07
		void                 CalculateMovementData(MovementArbitersContext& context) override;      // 08
		void                 Unk_09(MovementArbitersContext& context) override;                     // 09
		void                 RemoveMovementController() override;                                   // 0C
		void                 OnSaveGame(BSPathingStreamWrite* saveBuffer) override;                 // 0D
		void                 OnLoadGame(BSPathingStreamRead* loadBuffer) override;                  // 0E
		void                 AddAgent(MovementAgent** agent) override;                              // 0F
		void                 RemoveAgent(MovementAgent** agent) override;                           // 10
		void                 ClearAgents() override;                                                // 11

		// override (IMovementPlannerSetArbitration)
		void  SetMovementArbitrationVectorAdd(const BSTSmartPointer<MovementArbitrationVectorAdd>& arbitration) override;                      // 01
		void  SetMovementArbitrationMaxWeightPoint(const BSTSmartPointer<MovementArbitrationMaxWeightPoint>& arbitration) override;            // 02
		void  SetMovementArbitrationMaxWeightParameters(const BSTSmartPointer<MovementArbitrationMaxWeightParameters>& arbitration) override;  // 03
		void  ResetMovementParameters() override;                                                                                              // 04
		bool  AreMovementParametersInitialized() override;                                                                                     // 05
		float GetTimeBlocked() override;                                                                                                       // 06

		// members
		float                                                   timeBlocked;                             // 20
		bool                                                    movementParametersInitialized;           // 24
		uint32_t                                                ownerFormID;                             // 28
		BSTArray<BSTSmartPointer<IMovementPlannerAgent>>        agents;                                  // 30
		BSTSmartPointer<MovementArbitrationVectorAdd>           movementArbitrationVectorAdd;            // 48
		BSTSmartPointer<MovementArbitrationMaxWeightPoint>      movementArbitrationMaxWeightPoint;       // 50
		BSTSmartPointer<MovementArbitrationMaxWeightParameters> movementArbitrationMaxWeightParameters;  // 58
		MovementControllerAI*                                   controller;                              // 60
		void*                                                   plannerAgentReturnDataTracker;           // 68
	};
	static_assert(sizeof(MovementPlannerArbiter) == 0x70);
}
