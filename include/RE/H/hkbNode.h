#pragma once

#include "RE/H/hkStringPtr.h"
#include "RE/H/hkbBindable.h"
#include "RE/H/hkbContext.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkPointerMap.h"

namespace RE
{
	class hkbNodeChildInfo;
	class hkbNodeInternalStateInfo;

	class hkbNode : public hkbBindable
	{
	public:
		enum class GetChildrenFlagBits
		{
			kActiveOnly = 1 << 0,
			kGeneratorsOnly = 1 << 1,
			kIgnoreReferencedBehaviour = 1 << 2
		};

		enum class CloneState
		{
			kDefault = 0,
			kTemplate = 1,
			kClone = 2,
			kShareable = 3
		};

		struct ChildrenInfo
		{
			hkArray<hkbNodeChildInfo>& m_childInfos;			// 00
		};
		static_assert(sizeof(ChildrenInfo) == 0x8);

		inline static constexpr auto RTTI = RTTI_hkbNode;

		~hkbNode() override;  // 00

		// add
		virtual void Activate(const hkbContext& a_context);																																			// 04 - { return; }
		virtual void Update(const hkbContext& a_context, float a_timestep);																															// 05 - { userData |= 1; }
		virtual void HandleEvent(const hkbContext& a_context, hkbEvent event);																														// 06 - { return; }
		virtual void Deactivate(const hkbContext& a_context);																																		// 07 - { return; }
		virtual int GetMaxNumChildren(stl::enumeration<GetChildrenFlagBits, std::int32_t> flags);																									// 08 - { return 2; }
		virtual void GetChildren(stl::enumeration<GetChildrenFlagBits, std::int32_t> flags, ChildrenInfo& childrenInfo);																			// 09 - { return; }
		virtual bool IsValid(const hkbCharacter* character, hkStringPtr& errorString) const;																										// 0A - { return 1; }
		virtual void Precompute(const hkbContext& context);																																			// 0B - { return; }
		virtual hkbNode* CloneNode(hkbBehaviorGraph& rootBehavior) const;																															// 0C
		virtual hkReferencedObject* CreateInternalState();																																			// 0D - { return 0; }
		virtual void GetInternalState(hkReferencedObject& internalState) const;																														// 0E - { return; }
		virtual void GetInternalStateUser(const hkbBehaviorGraph& rootBehavior, hkReferencedObject& internalState);																					// 0F - { return; }
		virtual void SetInternalState(const hkReferencedObject& internalState);																														// 10 - { return; }
		virtual void SetInternalStateUser(const hkbContext& context, const hkReferencedObject& internalState, hkPointerMap<int16_t, const hkbNodeInternalStateInfo*>& nodeIdToInternalStateMap);	// 11 - { return; }
		virtual void GetActiveEvents(hkPointerMap<int, bool>& activeEvents) const;																													// 12 - { return; }
		virtual bool IsTransitionEffect() const;																																					// 13 - { return 0; }
		virtual void GetActiveVariablesSpecial(hkPointerMap<int, bool>& activeVariables) const;																										// 14 - { return; }
		virtual bool IsGenerator() const;																																							// 15 - { return 0; }
		virtual bool IsBehaviorGraph() const;																																						// 16 - { return 0; }

		// members
		std::uint64_t                              userData;    // 30
		hkStringPtr                                name;        // 38
		std::uint16_t                              id;          // 40
		stl::enumeration<CloneState, std::uint8_t> cloneState;  // 42
	};
	static_assert(sizeof(hkbNode) == 0x48);
}
