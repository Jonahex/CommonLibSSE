#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"

namespace RE
{
	class AnimationSetData
	{
	public:
		struct VariableData
		{
			BSFixedString							variable;		// 00
			int32_t									min;			// 08
			int32_t									max;			// 0C
		};
		static_assert(sizeof(VariableData) == 0x10);

		struct HashesData
		{
			BSTSmallArray<uint32_t>                 folderHashes;	// 00
			BSTSmallArray<BSTArray<uint32_t>>		nameHashes;		// 18
		};
		static_assert(sizeof(HashesData) == 0x40);

		struct AttackData
		{
			BSFixedString							event;			// 00
			BSTSmallArray<BSFixedString>*			clips;			// 08
			bool									unk10;			// 10
		};
		static_assert(sizeof(AttackData) == 0x18);

		BSTSmallArray<BSFixedString>				events;			// 00
		BSTArray<VariableData>                      variables;		// 18
		HashesData									hashes;			// 30
		BSTArray<AttackData>						attacks;		// 70
	};
	static_assert(sizeof(AnimationSetData) == 0x88);

	class AnimationSetDataSingleton : public BSTSingletonSDM<AnimationSetDataSingleton>
	{
	public:
		[[nodiscard]] static AnimationSetDataSingleton* GetSingleton()
		{
			REL::Relocation<AnimationSetDataSingleton**> singleton{ Offset::AnimationSetDataSingleton::Singleton };
			return *singleton;
		}

		BSTHashMap<BSFixedString, BSTArray<AnimationSetData>*>	projects;		// 08
	};
	static_assert(sizeof(AnimationSetDataSingleton) == 0x38);
}
