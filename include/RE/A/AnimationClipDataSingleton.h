#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	struct AnimationProjectClipData : BSIntrusiveRefCounted
	{
		struct EventData
		{
			BSFixedString eventName; // 00
			float         eventTime; // 08
		};
		static_assert(sizeof(EventData) == 0x10);

		// translations is a pointer to memory with the following content:
		// array of numTranslations NiPoint3 translations
		// array of numTranslations 16-bit float times
		// translations is a pointer to memory with the following content:
		// array of numTranslations NiQuaternion rotations
		// array of numTranslations 16-bit float times
		struct ClipRootMotionData
		{
			void*    translations;     // 00
			uint32_t numTranslations;  // 08
			void*    rotations;        // 10
			uint32_t numRotations;     // 18
			uint32_t pad1C;            // 1C
			float    clipLength;       // 20
		};
		static_assert(sizeof(ClipRootMotionData) == 0x28);

		// clipData is a map from clip name to pointer to memory with the following content:
		// float unk00;
		// uint16_t rootMotionDataIndex;
		// uint16_t numEvents;
		// array of numEvents EventDatas
		BSTHashMap<BSFixedString, void*> clipData;        // 08
		BSTArray<ClipRootMotionData>     rootMotionData;  // 38
		BSTArray<BSFixedString>          havokFiles;      // 50
	};
	static_assert(sizeof(AnimationProjectClipData) == 0x68);

	class AnimationClipDataSingleton : public BSTSingletonSDM<AnimationClipDataSingleton>
	{
	public:
		virtual ~AnimationClipDataSingleton();

		BSTHashMap<BSFixedString, BSTSmartPointer<AnimationProjectClipData>> projects;  // 10
		BSTArray<void*>                                                      unk40;     // 40
	};
	static_assert(sizeof(AnimationClipDataSingleton) == 0x58);
}
