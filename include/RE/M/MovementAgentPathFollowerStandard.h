#pragma once

#include "RE/C/CheckGoalReachedFunctor.h"
#include "RE/C/CheckParameterReachedFunctor.h"
#include "RE/C/CheckStoppedMovingFunctor.h"
#include "RE/I/IMovementHandlerAgent.h"
#include "RE/I/IMovementPathManagerAgent.h"
#include "RE/I/IMovementPlannerAgent.h"
#include "RE/I/IMovementPlayIdleResult.h"
#include "RE/I/IMovementQueryPathFollowing.h"
#include "RE/I/IMovementSetPathFollowing.h"
#include "RE/M/MovementAgent.h"
#include "RE/P/PathFollowerStateFollowPathToParameter.h"
#include "RE/P/PathFollowerStateKeepLastDirection.h"
#include "RE/P/PathFollowerStatePlayIdle.h"
#include "RE/P/PathFollowerStateTurnToAngle.h"

namespace RE
{
	class MovementAgentPathFollowerStandard :
		public MovementAgent,
		public IMovementPlannerAgent,
		public IMovementPathManagerAgent,
		public IMovementQueryPathFollowing,
		public IMovementSetPathFollowing,
		public IMovementPlayIdleResult,
		public IMovementHandlerAgent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgentPathFollowerStandard;

		enum class StateType
		{
			NoPath = 0x0,
			NewPathStarted = 0x1,
			PlayingIdleToPath = 0x2,
			TurningToPath = 0x3,
			SlowingDown = 0x4,
			Unk5 = 0x5,
			PlayingIdleToDestination = 0x6,
			TurningToDestination = 0x7,
			StandingKeepingLastDirection = 0x8,
			MovingKeepingLastDirection = 0xA,
			NoDetailedPath = 0xB,
			PathComplete = 0xC,
			MovingAlongPath = 0xD,
			WaitingToPlayIdleToPath = 0xE,
			WaitingToPlayIdleToDestination = 0xF,
		};

		~MovementAgentPathFollowerStandard() override;  // 00

		// override (MovementAgent)
		const BSFixedString& GetName() const override;                                          // 01
		MovementAgentType    GetType() override;                                                // 02
		IMovementInterface*  GetInterfaceByName(BSFixedString* name) override;                  // 03
		void                 SetMovementController(MovementControllerAI* controller) override;  // 04
		void                 Activate() override;                                               // 06
		void                 Initialize(BSPathingStreamSimpleBufferRead* buffer) override;      // 07
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
		void                 OnPathRestart(const BSTSmartPointer<BSPathingRequest>& pathingRequest) override;                                                         // 04
		void                 OnPathCleared() override;                                                                                                                // 06

		// override (IMovementQueryPathFollowing)
		bool CanCompletePath() override;                                                                                                                             // 01
		bool IsPathFailed() override;                                                                                                                                // 02
		bool IsPathInProgress() override;                                                                                                                            // 03
		bool IsMovingAlongPath() override;                                                                                                                           // 04
		bool GetDestinationPositionAndWidth(NiPoint3& outPosition, float& outWidth) override;                                                                        // 05
		bool GetDistanceToGoal(float& outDistance) override;                                                                                                         // 06
		bool GetTargetAngle(NiPoint3& outAngle) override;                                                                                                            // 07
		bool HasMovementTarget() override;                                                                                                                           // 08
		bool GetPathPositionByTime(float deltaTime, NiPoint3& outPosition) override;                                                                                 // 09
		bool GetPathPositionAndDirectionByTime(float deltaTime, NiPoint3& outPosition, NiPoint3& outDirection) override;                                             // 0A
		bool GetMaxPathSpeed(float rotationSpeedZ, float angularAcceleration, float deceleration, float rotateWhileMovingRun, float& outSpeed) override;             // 0B
		bool GetPathPositionAndDirectionByDistance(float distance, NiPoint3& outPosition, NiPoint3& outDirection) override;                                          // 0C
		bool GetPathPositionByDistance(float distance, NiPoint3& outPosition) override;                                                                              // 0D
		bool GetClosestPathPositionAndDirection(const NiPoint3& targetPosition, float& outPathParameter, NiPoint3& outPosition, NiPoint3& outDirection) override;    // 0E
		bool GetPathDistanceToParameter(float pathParameter, float& outDistance) override;                                                                           // 0F
		bool GetPathDistanceLeft(float& outDistance) override;                                                                                                       // 10
		bool GetPathDistanceLeftAndFinalPosition(NiPoint3& outPosition, float& outDistance) override;                                                                // 11
		bool GetPathDoor(BSTSmartPointer<MovementMessage>& outDoorMovementMessage, uint32_t& outDoorPathingPointIndex, PathingPoint& outDoorPathingPoint) override;  // 12
		bool AcceptNodeVisitor(const INodeVisitor& visitor) override;                                                                                                // 13
		bool GetDirectionAlongPath(NiPoint3& outDirection) override;                                                                                                 // 14

		// override (IMovementSetPathFollowing)
		Result SetPathFollowing(bool isFollowing) override;  // 01

		// override (IMovementPlayIdleResult)
		void     OnPlayIdle(const BSFixedString& eventName, bool isIdleStarted) override;  // 01
		void     IncRef() const override;                                                  // 02
		uint32_t DecRef() override;                                                        // 03

		// override (IMovementHandlerAgent)
		const BSFixedString& GetHandlerAgentName() override;                    // 01
		void                 HandleMovement(HandlerContext& context) override;  // 02
		void                 HandleMovementVirtual(float* deltaTime) override;  // 03

		// members
		PathFollowerStatePlayIdle                            statePlayIdle;                 // 48
		PathFollowerStateTurnToAngle                         stateTurnToAngle;              // 60
		PathFollowerStateFollowPathToParameter               stateFollowPathToParameter;    // 80
		PathFollowerStateKeepLastDirection                   stateKeepLastDirection;        // A0
		CheckParameterReachedFunctor                         checkParameterReachedFunctor;  // C0
		CheckGoalReachedFunctor                              checkGoalReachedFunctor;       // D0
		CheckStoppedMovingFunctor                            checkStoppedMovingFunctor;     // E0
		NiPoint3                                             movementDirection;             // E8
		NiPoint3                                             expectedPathPosition;          // F4
		float                                                currentPathParameter;          // 100
		uint32_t                                             ownerFormID;                   // 104
		MovementControllerAI*                                movementController;            // 108
		BSReadWriteLock                                      lock;                          // 110
		stl::enumeration<StateType, int32_t>                 currentStateType;              // 118
		BSTSmartPointer<BSPathingRequest>                    pathingRequest;                // 120
		BSTSmartPointer<BSPathingSolution>                   pathingSolution;               // 128
		BSTSmartPointer<PathFollowerStatePlayIdle::IdleData> idleData;                      // 130
		void*                                                unk138;                        // 138
		void*                                                unk140;                        // 140
		IPathFollowerState*                                  currentState;                  // 148
		float                                                finalPathParameter;            // 150
		float                                                actionPathParameter;           // 154
		float                                                pathSpeed;                     // 158
		int32_t                                              actionPathingPointIndex;       // 15C
		bool                                                 isAllowRotationState;          // 160
	};
	static_assert(sizeof(MovementAgentPathFollowerStandard) == 0x168);
}
