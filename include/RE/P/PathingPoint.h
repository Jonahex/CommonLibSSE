#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class PathingCell;
	struct BSNavmeshInfo;

	struct PathingPoint
	{
		NiPoint3                  position;          // 00
		BSNavmeshInfo*            navmeshInfo;       // 10
		BSTArray<BSNavmeshInfo*>* cellNavmeshInfos;  // 18
		PathingCell*              pathingCell;       // 20
		std::int16_t              triIndex;          // 28
		bool                      unk2A;             // 2A
		bool                      unk2B;             // 2B
	};
	static_assert(sizeof(PathingPoint) == 0x30);
}
