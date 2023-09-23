#pragma once

#include "RE/I/IMovementHandlerAgent.h"
#include "RE/I/IMovementPathManagerAgent.h"
#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementQueryFlight.h"
#include "RE/I/IMovementQueryPathFollowing.h"
#include "RE/M/MovementAgent.h"

namespace RE
{
	class MovementAgentPathFollowerFlight :
		public MovementAgent,
		public IMovementPlannerAgent,
		public IMovementPathManagerAgent,
		public IMovementQueryPathFollowing,
		public IMovementQueryFlight
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerFlight;

		enum class State
		{
			NoPath = 0x0,
			PathInProgress = 0x1,
			PathComplete = 0x2,
		};

		struct InterpolatedPathPoint
		{
			NiPoint3 position; // 00
			float    cumulativePassedDistance; // 0C
		};
		static_assert(sizeof(InterpolatedPathPoint) == 0x10);

		struct SubPath
		{
			BSTArray<NiPoint3>              originalPathPoints; // 00
			BSTArray<InterpolatedPathPoint> interpolatedPoints; // 18
		};
		static_assert(sizeof(SubPath) == 0x30);

		~MovementAgentPathFollowerFlight() override;  // 00

		// override (MovementAgent)
		const BSFixedString& GetName() const override;                                          // 01
		MovementAgentType    GetType() override;                                                // 02
		IMovementInterface*  GetInterfaceByName(BSFixedString* name) override;                  // 03
		void                 SetMovementController(MovementControllerAI* controller) override;  // 04
		void                 Activate() override;                                               // 06
		void                 RemoveMovementController() override;                               // 0A
		void                 OnSaveGame(BSPathingStreamWrite* a2) override;                     // 0B
		void                 OnLoadGame(BSPathingStreamRead* a2) override;                      // 0C

		// override (IMovementPlannerAgent)
		const BSFixedString& GetPlannerAgentName() override;                                    // 01
		void                 PlanMovement(float* deltaTime, PlannerContext& context) override;  // 02
		void                 PlanMovementVirtual(float* deltaTime, bool&) override;             // 03

		// override (IMovementPathManagerAgent)
		const BSFixedString& GetPathManagerAgentName() override;                                                                                                      // 01
		void                 OnNewPath(const BSTSmartPointer<BSPathingRequest>& pathingRequest, const BSTSmartPointer<BSPathingSolution>& pathingSolution) override;  // 02
		void                 ProcessPath(MovementArbitersContext& context, PathFollowingInfo& point) override;                                                        // 03
		void                 OnPathCleared() override;                                                                                                                // 06

		// override (IMovementQueryPathFollowing)
		bool CanCompletePath() override;                                                                                                                             // 01
		bool IsPathFailed() override;                                                                                                                                // 02
		bool IsPathInProgress() override;                                                                                                                            // 03
		bool IsMovingAlongPath() override;                                                                                                                           // 04
		bool GetDestinationPositionAndWidth(NiPoint3& outPosition, float& outWidth) override;                                                                        // 05
		bool GetDistanceToGoal(float& outDistance) override;                                                                                                         // 06
		bool GetPathPositionByTime(float deltaTime, NiPoint3& outPosition) override;                                                                                 // 09
		bool GetPathPositionAndDirectionByTime(float deltaTime, NiPoint3& outPosition, NiPoint3& outDirection) override;                                             // 0A
		
		// add
		virtual bool Unk_0D(void);  // 0D

		// members
		stl::enumeration<State, int32_t>   state;                        // 38
		float                              subPathFlownDistance;         // 3C
		BSTSmartPointer<BSPathingRequest>  pathingRequest;               // 40
		BSTSmartPointer<BSPathingSolution> pathingSolution;              // 48
		float                              pathLength;                   // 50
		float                              finishedSubPathsTotalLength;  // 54
		uint32_t                           nextPathPoint;                // 58
		uint32_t                           firstSubPathPoint;            // 5C
		SubPath                            currentSubPath;               // 60
		uint32_t                           ownerFormID;                  // 90
		MovementControllerAI*              controller;                   // 98
		BSReadWriteLock                    lock;                         // A0
	};
	static_assert(sizeof(MovementAgentPathFollowerFlight) == 0xA8);
}
