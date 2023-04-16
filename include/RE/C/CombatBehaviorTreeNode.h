#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class CombatBehaviorTreeControl;

	class CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeNode;

		virtual ~CombatBehaviorTreeNode();                                                                                 // 00
		virtual const char*                GetName() const;                                                                // 01
		virtual CombatBehaviorTreeControl* Push(CombatBehaviorTreeControl* control) const;                                 // 02
		virtual void                       Pop(CombatBehaviorTreeControl* control) const;                                  // 03
		virtual void                       OnChildFailed(CombatBehaviorTreeControl* control) const;                        // 04
		virtual void                       OnInterrupted(CombatBehaviorTreeControl* control) const;                        // 05
		virtual void                       SaveGame(CombatBehaviorTreeControl* control, BGSSaveGameBuffer* buffer) const;  // 06
		virtual void                       LoadGame(CombatBehaviorTreeControl* control, BGSLoadGameBuffer* buffer) const;  // 07
		virtual bool                       Unk08(CombatBehaviorTreeControl* control) const;                                // 08
		virtual BSFixedString*             Unk09() const = 0;                                                              // 09

		// members
		BSFixedString                          name;      // 08
		CombatBehaviorTreeNode*                parent;    // 10
		BSStaticArray<CombatBehaviorTreeNode*> children;  // 18
	};
	static_assert(sizeof(CombatBehaviorTreeNode) == 0x28);
}
