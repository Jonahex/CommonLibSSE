#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	class BSPathingRequest;
	class BSPathingSolution;

	enum class PathingState
	{
		Invalid = 0xFFFFFFFF,
		NoPath = 0x0,
		PathRequested = 0x1,
		PathInProgress = 0x2,
		PathComplete = 0x3,
	};

	class IMovementQueryPathingState : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementQueryPathingState;

		enum class PathingStateQueryResult
		{
			False = 0x0,
			True = 0x1,
			Undefined = 0x2,
		};

		~IMovementQueryPathingState() override;  // 00

		// add
		virtual bool                    IsCurrentPathingRequest(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;                 // 01
		virtual bool                    IsChosenPathingSolution(const BSTSmartPointer<BSPathingSolution>& pathingSolution) = 0;               // 02
		virtual PathingStateQueryResult IsPathingRequestComplete(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;                // 03
		virtual PathingStateQueryResult IsPathingRequestProcessed(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;               // 04
		virtual bool                    IsPathingRequestProcessedButIncomplete(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;  // 05
		virtual bool                    IsPathingRequestProcessedButNotStarted(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;  // 06
		virtual PathingState            GetCurrentPathingState() = 0;                                                                         // 07
		virtual PathingState            GetPathingState(const BSTSmartPointer<BSPathingRequest>& pathingRequest) = 0;                         // 08
		virtual bool                    IsCurrentPathingRequestNotProcessed() = 0;                                                            // 09
		virtual bool                    IsCurrentPathingRequestComplete() = 0;                                                                // 0A
		virtual bool                    IsCurrentPathingRequestProcessedButIncomplete() = 0;                                                  // 0B
		virtual bool                    IsCurrentPathingRequestInProgress() = 0;                                                              // 0C
		virtual bool                    IsCurrentPathingRequestProcessedButNotStarted() = 0;                                                  // 0D
	};
	static_assert(sizeof(IMovementQueryPathingState) == 0x8);
}
