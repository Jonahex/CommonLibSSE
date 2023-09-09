#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IMovementQueryPathingState.h"
#include "RE/I/IMovementSetGoal.h"
#include "RE/M/MovementArbiter.h"

namespace RE
{
	class IMovementPathManagerAgent;
	class IMovementPathManagerDataTracker;
	class MovementControllerAI;

	class MovementPathManagerArbiter :
		public MovementArbiter,            // 000
		public IMovementSetGoal,           // 001
		public IMovementQueryPathingState  // 002
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementPathManagerArbiter;

		~MovementPathManagerArbiter() override;  // 00

		// override (MovementArbiter)
		const BSFixedString& GetPipelineStageName() const override;                             // 01
		const BSFixedString& GetArbiterName() const override;                                   // 02
		MovementArbiterType  GetType() override;                                                // 03
		void                 SetMovementController(MovementControllerAI* controller) override;  // 04
		void                 Activate() override;                                               // 06
		void                 Unk_08(void* context) override;                                    // 08
		void                 Unk_09(void* context) override;                                    // 09
		void                 RemoveMovementController() override;                               // 0C
		void                 OnSaveGame(BSPathingStreamWrite* saveBuffer) override;             // 0D
		void                 OnLoadGame(BSPathingStreamRead* loadBuffer) override;              // 0E
		void                 AddAgent(MovementAgent** agent) override;                          // 0F
		void                 RemoveAgent(MovementAgent** agent) override;                       // 10
		void                 ClearAgents() override;                                            // 11

		// override (IMovementSetGoal)
		void SetGoal(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;                                                                        // 01
		void SetGoalAndSolution(const BSTSmartPointer<BSPathingSolution>& pathingSolution, const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;  // 02
		void ResetGoal() override;                                                                                                                             // 03
		void RestartGoal() override;                                                                                                                           // 04

		// override (IMovementQueryPathingState)
		bool                    IsCurrentPathingRequest(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;                 // 01
		bool                    IsChosenPathingSolution(const BSTSmartPointer<BSPathingSolution>& pathingSolution) override;               // 02
		PathingStateQueryResult IsPathingRequestComplete(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;                // 03
		PathingStateQueryResult IsPathingRequestProcessed(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;               // 04
		bool                    IsPathingRequestProcessedButIncomplete(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;  // 05
		bool                    IsPathingRequestProcessedButNotStarted(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;  // 06
		PathingState            GetCurrentPathingState() override;                                                                         // 07
		PathingState            GetPathingState(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;                         // 08
		bool                    IsCurrentPathingRequestNotProcessed() override;                                                            // 09
		bool                    IsCurrentPathingRequestComplete() override;                                                                // 0A
		bool                    IsCurrentPathingRequestProcessedButIncomplete() override;                                                  // 0B
		bool                    IsCurrentPathingRequestInProgress() override;                                                              // 0C
		bool                    IsCurrentPathingRequestProcessedButNotStarted() override;                                                  // 0D

		// members
		BSTArray<BSTSmartPointer<IMovementPathManagerAgent>> pathManagerAgents;          // 028
		MovementControllerAI*                                movementController;         // 040
		PathingState                                         pathingState;               // 048
		BSTSmartPointer<BSPathingRequest>                    pathingRequest;             // 050
		BSTSmartPointer<BSPathingSolution>                   chosenPathingSolution;      // 058
		BSTSmartPointer<BSPathingSolutionsContainer>         availablePathingSolutions;  // 060
		BSReadWriteLock                                      lock;                       // 068
		uint32_t                                             ownerFormID;                // 070
		IMovementPathManagerDataTracker*                     dataTracker;                // 078
	};
	static_assert(sizeof(MovementPathManagerArbiter) == 0x80);
}
