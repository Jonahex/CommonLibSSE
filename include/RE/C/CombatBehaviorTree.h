#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"

namespace RE
{
	class CombatBehaviorTreeRootNode;

	class CombatBehaviorTree
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTree;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTree;

		static const BSTHashMap<BSFixedString, CombatBehaviorTree*>& GetStorage()
		{
			using func_t = decltype(&CombatBehaviorTree::GetStorage);
			REL::Relocation<func_t> func{ RELOCATION_ID(32551, 33306) };
			return func();
		}

		virtual void Setup();  // 00

		// members
		BSFixedString               name;
		CombatBehaviorTreeRootNode* rootNode;
	};
	static_assert(sizeof(CombatBehaviorTree) == 0x18);
}
