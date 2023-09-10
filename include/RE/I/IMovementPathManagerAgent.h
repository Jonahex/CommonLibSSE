#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IPipelineStageInterface.h"
#include "RE/P/PathingPoint.h"

namespace RE
{
	class BSPathingRequest;
	class BSPathingSolution;
	class MovementArbitersContext;

	class IMovementPathManagerAgent : public IPipelineStageInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPathManagerAgent;

		enum class PathFollowingState
		{
			FollowingNormally = 0x0,
			AvoidingObstacle = 0x1,
			StrayedTooFarFromPath = 0x3,
			PathBlocked = 0x4,
		};

		struct PathFollowingInfo
		{
			stl::enumeration<PathFollowingState, std::uint32_t> state;            // 00
			PathingPoint                                        newPathingPoint;  // 08
			float                                               pathRadius;       // 38
		};
		static_assert(sizeof(PathFollowingInfo) == 0x40);

		~IMovementPathManagerAgent() override;  // 00

		// add
		virtual const BSFixedString& GetPathManagerAgentName() = 0;                                                                                                      // 01
		virtual void                 OnNewPath(const BSTSmartPointer<BSPathingRequest>& pathingRequest, const BSTSmartPointer<BSPathingSolution>& pathingSolution) = 0;  // 02
		virtual void                 ProcessPath(MovementArbitersContext& context, PathFollowingInfo& point) = 0;                                                        // 03
		virtual void                 OnPathRestart(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;                                                         // 04
		virtual void                 OnPathComplete(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;                                                        // 05
		virtual void                 OnPathCleared() = 0;                                                                                                                // 06
	};
	static_assert(sizeof(IMovementPathManagerAgent) == 0x8);
}
