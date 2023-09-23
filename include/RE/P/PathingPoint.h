#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class PathingCell;
	struct BSNavmeshInfo;

	struct PathingPoint
	{
		enum class Flags1
		{
			SingleNavmeshInfo = 0x1,
			DataLocked = 0x2,
		};

		enum class Flags2
		{
			HasNavmeshInfo = 0x1,
			HighLevelPath = 0x2,
			PathEnd = 0x4,
			Unk08 = 0x8,
			Unk10 = 0x10,
		};

		NiPoint3                               position;          // 00
		BSNavmeshInfo*                         navmeshInfo;       // 10 - set if cell has single navmesh
		BSTArray<BSNavmeshInfo*>*              cellNavmeshInfos;  // 18 - set if cell has multiple navmeshes
		BSTSmartPointer<PathingCell>           pathingCell;       // 20
		std::int16_t                           triIndex;          // 28
		stl::enumeration<Flags1, std::uint8_t> flags1;            // 2A
		stl::enumeration<Flags2, std::uint8_t> flags2;            // 2B
	};
	static_assert(sizeof(PathingPoint) == 0x30);
}
