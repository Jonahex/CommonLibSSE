#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/PathingPoint.h"

namespace RE
{
	class MovementMessageActivateDoor;

	struct BSPathingSolution : public BSIntrusiveRefCounted
	{
	public:
		struct HighLevelPathingPoint : PathingPoint
		{
		public:
			// members
			BSTSmartPointer<MovementMessageActivateDoor> movementMessage;  // 30
		};
		static_assert(sizeof(HighLevelPathingPoint) == 0x38);

		struct DetailedPathingPoint : PathingPoint
		{
		public:
			// members
			BSTSmartPointer<MovementMessageActivateDoor> movementMessage;  // 30
			NiPoint3                                     pathTangent;      // 38
		};
		static_assert(sizeof(DetailedPathingPoint) == 0x48);

		// members
		BSTSmallArray<HighLevelPathingPoint, 2> highLevelPath;                // 08
		uint32_t                                detailedPathFirstPointIndex;  // 88
		uint32_t                                detailedPathLastPointIndex;   // 8C
		BSTArray<DetailedPathingPoint>          detailedPath;                 // 90
		uint8_t                                 unkA8;                        // A8
		uint8_t                                 unkA9;                        // A9
	};
	static_assert(sizeof(BSPathingSolution) == 0xB0);

	struct BSPathingSolutionsContainer : public BSIntrusiveRefCounted
	{
	public:
		struct BSPathingSolutionHolder
		{
		public:
			// members
			bool                               isBuilt;  // 00
			BSTSmartPointer<BSPathingSolution> unk08;    // 08
		};
		static_assert(sizeof(BSPathingSolutionHolder) == 0x10);

		// members
		BSTSmallArray<BSPathingSolutionHolder> solutions;  // 08
		BSSpinLock                             lock;       // 28
	};
	static_assert(sizeof(BSPathingSolutionsContainer) == 0x30);
}
