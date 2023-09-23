#pragma once

#include "RE/B/BSPathingSolution.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	class MovementMessage;
	class NiPoint3;

	struct PathingPoint;

	class IMovementQueryPathFollowing : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryPathFollowing;

		class INodeVisitor
		{
			inline static constexpr auto RTTI = RTTI_IMovementQueryPathFollowing__INodeVisitor;

			virtual ~INodeVisitor(); // 00

			// add
			virtual bool Visit(const BSPathingSolution::DetailedPathingPoint& point) = 0;
		};

		~IMovementQueryPathFollowing() override;  // 00

		// add
		virtual bool CanCompletePath() = 0;                                                                                                                         // 01
		virtual bool IsPathFailed() = 0;                                                                                                                            // 02
		virtual bool IsPathInProgress() = 0;                                                                                                                        // 03
		virtual bool IsMovingAlongPath() = 0;                                                                                                                       // 04
		virtual bool GetDestinationPositionAndWidth(NiPoint3& outPosition, float& outWidth) = 0;                                                                    // 05
		virtual bool GetDistanceToGoal(float& outDistance) = 0;                                                                                                     // 06
		virtual bool GetTargetAngle(NiPoint3& outAngle);                                                                                                            // 07
		virtual bool HasMovementTarget();                                                                                                                           // 08
		virtual bool GetPathPositionByTime(float deltaTime, NiPoint3& outPosition);                                                                                 // 09
		virtual bool GetPathPositionAndDirectionByTime(float deltaTime, NiPoint3& outPosition, NiPoint3& outDirection);                                             // 0A
		virtual bool GetMaxPathSpeed(float rotationSpeedZ, float angularAcceleration, float deceleration, float rotateWhileMovingRun, float& outSpeed);             // 0B
		virtual bool GetPathPositionAndDirectionByDistance(float distance, NiPoint3& outPosition, NiPoint3& outDirection);                                          // 0C
		virtual bool GetPathPositionByDistance(float distance, NiPoint3& outPosition);                                                                              // 0D
		virtual bool GetClosestPathPositionAndDirection(const NiPoint3& targetPosition, float& outPathParameter, NiPoint3& outPosition, NiPoint3& outDirection);    // 0E
		virtual bool GetPathDistanceToParameter(float pathParameter, float& outDistance);                                                                           // 0F
		virtual bool GetPathDistanceLeft(float& outDistance);                                                                                                       // 10
		virtual bool GetPathDistanceLeftAndFinalPosition(NiPoint3& outPosition, float& outDistance);                                                                // 11
		virtual bool GetPathDoor(BSTSmartPointer<MovementMessage>& outDoorMovementMessage, uint32_t& outDoorPathingPointIndex, PathingPoint& outDoorPathingPoint);  // 12
		virtual bool AcceptNodeVisitor(const INodeVisitor& visitor);                                                                                                // 13
		virtual bool GetDirectionAlongPath(NiPoint3& outDirection);                                                                                                 // 14
	};
	static_assert(sizeof(IMovementQueryPathFollowing) == 0x8);
}
