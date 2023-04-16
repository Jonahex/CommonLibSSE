#pragma once

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	class CombatBehaviorTreeRootNode : public CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeRootNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeRootNode;

		// override (CombatBehaviorTreeNode)
		~CombatBehaviorTreeRootNode() override;                                                                             // 00
		CombatBehaviorTreeControl* Push(CombatBehaviorTreeControl* control) const override;                                 // 02
		void                       OnChildFailed(CombatBehaviorTreeControl* control) const override;                        // 04
		void                       OnInterrupted(CombatBehaviorTreeControl* control) const override;                        // 05
		void                       SaveGame(CombatBehaviorTreeControl* control, BGSSaveGameBuffer* buffer) const override;  // 06
		void                       LoadGame(CombatBehaviorTreeControl* control, BGSLoadGameBuffer* buffer) const override;  // 07
		bool                       Unk08(CombatBehaviorTreeControl* control) const override;                                // 08
		BSFixedString*             Unk09() const override;                                                                  // 09
	};
	static_assert(sizeof(CombatBehaviorTreeRootNode) == 0x28);
}
