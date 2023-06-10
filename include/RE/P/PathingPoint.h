#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class PathingCell;
	struct BSNavmeshInfo;

	struct PathingPoint
	{
		NiPoint3                  position;
		BSNavmeshInfo*            navmeshInfo;
		BSTArray<BSNavmeshInfo*>* cellNavmeshInfos;
		PathingCell*              pathingCell;
		std::int16_t              triIndex;
		bool                      unk2A;
		bool                      unk2B;
	};
	static_assert(sizeof(PathingPoint) == 0x30);
}
