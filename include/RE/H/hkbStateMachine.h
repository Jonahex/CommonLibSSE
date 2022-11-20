#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbBindable.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbStateChooser;

	class hkbStateMachine : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateMachine;

		enum class StartStateMode
		{
			kDefault = 0,
			kSync = 1,
			kRandom = 2,
			kChooser = 3
		};

		enum class StateMachineSelfTransitionMode
		{
			kNoTransition = 0,
			kTransitionToStartState = 1,
			kForceTransitionToStartState = 2
		};

		class StateInfo : public hkbBindable
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__StateInfo;

			~StateInfo() override;  // 00

			// members
			std::uint64_t unk30;  // 30
			std::uint64_t unk38;  // 38
			std::uint64_t unk40;  // 40
			std::uint64_t unk48;  // 48
			std::uint64_t unk50;  // 50
			std::uint64_t unk58;  // 58
			std::uint64_t unk60;  // 60
			std::uint64_t unk68;  // 68
			std::uint64_t unk70;  // 70
		};
		static_assert(sizeof(StateInfo) == 0x78);

		class TransitionInfoArray : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__TransitionInfoArray;

			~TransitionInfoArray() override;  // 00

			// members
			std::uint64_t unk10;  // 10
			std::uint64_t unk18;  // 18
		};
		static_assert(sizeof(TransitionInfoArray) == 0x20);

		~hkbStateMachine() override;  // 00

		// override (hkbGenerator)
		hkClass*			GetClassType() const override;																																							// 01
		void				CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;																						// 02
		void				CollectBindables(hkbBindableCollector& collector) override;																																// 03
		void				Activate(const hkbContext& a_context) override;																																			// 04
		void				Update(const hkbContext& a_context, float a_timestep) override;																															// 05
		void				HandleEvent(const hkbContext& a_context, hkbEvent event) override;																														// 06
		void				Deactivate(const hkbContext& a_context) override;																																		// 07
		int					GetMaxNumChildren(stl::enumeration<GetChildrenFlagBits, std::int32_t> flags) override;																									// 08
		void				GetChildren(stl::enumeration<GetChildrenFlagBits, std::int32_t> flags, ChildrenInfo& childrenInfo) override;																			// 09
		bool				IsValid(const hkbCharacter* character, hkStringPtr& errorString) const override;																										// 0A
		hkbNode*            CloneNode(hkbBehaviorGraph& rootBehavior) const override;																																// 0C
		hkReferencedObject* CreateInternalState() override;																																							// 0D
		void                GetInternalState(hkReferencedObject& internalState) const override;																														// 0E
		void                GetInternalStateUser(const hkbBehaviorGraph& rootBehavior, hkReferencedObject& internalState) override;																					// 0F
		void                SetInternalState(const hkReferencedObject& internalState) override;																														// 10
		void                SetInternalStateUser(const hkbContext& context, const hkReferencedObject& internalState, hkPointerMap<int16_t, const hkbNodeInternalStateInfo*>& nodeIdToInternalStateMap) override;	// 11
		void                GetActiveEvents(hkPointerMap<int, bool>& activeEvents) const override;																													// 12
		void                GetActiveVariablesSpecial(hkPointerMap<int, bool>& activeVariables) const override;																										// 14
		void                Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output) override;                                                            // 17
		bool				CanRecycleOutput() override;																																							// 18 - { return 1; }
		void				UpdateSync(const hkbContext& a_context) override;																																		// 19
		void                PreUpdate(const hkbContext& context, float timestep) override;																															// 1B - { echoNextUpdate = true; }

		// members
		hkbEvent                                                       eventToSendWhenStateOrTransitionChanges;  // 048
		hkRefPtr<hkbStateChooser>                                      startStateChooser;                        // 060
		std::int32_t                                                   startStateID;                             // 068
		std::int32_t                                                   returnToPreviousStateEventID;             // 06C
		std::int32_t                                                   randomTransitionEventID;                  // 070
		std::int32_t                                                   transitionToNextHigherStateEventID;       // 074
		std::int32_t                                                   transitionToNextLowerStateEventID;        // 078
		std::int32_t                                                   syncVariableIndex;                        // 07C
		std::int32_t                                                   currentStateID;                           // 080
		bool                                                           wrapAroundStateID;                        // 084
		std::int8_t                                                    maxSimultaneousTransitions;               // 085
		stl::enumeration<StartStateMode, std::uint8_t>                 startStateMode;                           // 086
		stl::enumeration<StateMachineSelfTransitionMode, std::uint8_t> selfTransitionMode;                       // 087
		bool                                                           isActive;                                 // 088
		std::uint8_t                                                   pad41;                                    // 089
		std::uint16_t                                                  pad42;                                    // 08A
		std::uint32_t                                                  pad44;                                    // 08C
		hkArray<StateInfo*>                                            states;                                   // 090
		hkRefPtr<TransitionInfoArray>                                  wildcardTransitions;                      // 0A0
		hkRefVariant                                                   stateIDToIndexMap;                        // 0A8
		hkArray<hkRefVariant>                                          activeTransitions;                        // 0B0
		hkArray<hkRefVariant>                                          transitionFlags;                          // 0C0
		hkArray<hkRefVariant>                                          wildcardTransitionFlags;                  // 0D0
		hkArray<hkRefVariant>                                          delayedTransitions;                       // 0E0
		float                                                          timeInState;                              // 0F0
		float                                                          lastLocalTime;                            // 0F4
		std::int32_t                                                   previousStateID;                          // 0F8
		std::int32_t                                                   nextStartStateIndexOverride;              // 0FC
		bool                                                           stateOrTransitionChanged;                 // 100
		bool                                                           echoNextUpdate;                           // 101
		std::uint16_t                                                  currentStateIndexAndEntered;              // 102
		std::uint32_t                                                  pad0BC;                                   // 104
	};
	static_assert(sizeof(hkbStateMachine) == 0x108);
}
