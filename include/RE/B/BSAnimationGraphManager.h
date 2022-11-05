#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/H/hkbVariableValue.h"

namespace RE
{
	class BSAnimationGraphChannel;
	class BShkbAnimationGraph;
	struct BSAnimationGraphEvent;

	struct AnimVariableCacheInfo
	{
	public:
		// members
		BSFixedString     variableName;  // 00
		hkbVariableValue* variable;      // 08
	};
	static_assert(sizeof(AnimVariableCacheInfo) == 0x10);

	struct BSAnimationGraphVariableCache
	{
	public:
		// members
		BSTArray<AnimVariableCacheInfo> variableCache;  // 00
		mutable BSSpinLock              updateLock;     // 18
#ifdef SKYRIM_SUPPORT_AE
		mutable BSSpinLock graphLock;  // 20
#endif
		BSTSmartPointer<BShkbAnimationGraph> animationGraph;  // 28 - smart ptr
	};
#ifndef SKYRIM_SUPPORT_AE
	static_assert(sizeof(BSAnimationGraphVariableCache) == 0x28);
#else
	static_assert(sizeof(BSAnimationGraphVariableCache) == 0x30);
#endif

	BSSmartPointer(BSAnimationGraphManager);

	class BSAnimationGraphManager :
		public BSTEventSink<BSAnimationGraphEvent>,  // 00
		public BSIntrusiveRefCounted                 // 08
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSAnimationGraphManager;

		struct AnimationVariable
		{
		public:
			union Value
			{
				bool         b;
				std::int32_t i;
				float        f;
			};
			static_assert(sizeof(Value) == 0x4);

			// members
			BSFixedString name;   // 00
			Value*        value;  // 08
		};
		static_assert(sizeof(AnimationVariable) == 0x10);

		~BSAnimationGraphManager() override;  // 00

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent* a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;  // 01

		// members
		std::uint32_t                                       pad0C;                 // 0C
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>>  boundChannels;         // 10
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>>  bumpedChannels;        // 28
		BSTSmallArray<BSTSmartPointer<BShkbAnimationGraph>> graphs;                // 40
		BSTArray<BSAnimationGraphManagerPtr>                subManagers;           // 58
		BSAnimationGraphVariableCache                       variableCache;         // 70
		mutable BSSpinLock                                  updateLock;            // 98
		mutable BSSpinLock                                  dependentManagerLock;  // A0
		std::uint32_t                                       activeGraph;           // A8
		std::uint32_t                                       generateDepth;         // A8
	};
#ifndef SKYRIM_SUPPORT_AE
	static_assert(sizeof(BSAnimationGraphManager) == 0xB0);
#else
	static_assert(sizeof(BSAnimationGraphManager) == 0xB8);
#endif
}
