#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbBindable.h"
#include "RE/H/hkbEvent.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbCondition;
	class hkbEventProperty;
	class hkbStateChooser;
	class hkbTransitionEffect;

	class hkbStateMachine : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateMachine;
		inline static constexpr auto VTABLE = VTABLE_hkbStateMachine;

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

		class EventPropertyArray : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__EventPropertyArray;

			~EventPropertyArray() override;				// 00

			hkArray<hkbEventProperty> m_events;			// 10
		};
		static_assert(sizeof(EventPropertyArray) == 0x20);

		struct TimeInterval
		{
			int32_t m_enterEventId;		// 00
			int32_t m_exitEventId;		// 04
			float	m_enterTime;		// 08
			float   m_exitTime;			// 0C
		};
		static_assert(sizeof(TimeInterval) == 0x10);

		class TransitionInfo
		{
		public:
			enum class TransitionFlags
			{
				FLAG_USE_TRIGGER_INTERVAL = 1,
				FLAG_USE_INITIATE_INTERVAL = 2,
				FLAG_UNINTERRUPTIBLE_WHILE_PLAYING = 4,
				FLAG_UNINTERRUPTIBLE_WHILE_DELAYED = 8,
				FLAG_DELAY_STATE_CHANGE = 16,
				FLAG_DISABLED = 32,
				FLAG_DISALLOW_RETURN_TO_PREVIOUS_STATE = 64,
				FLAG_DISALLOW_RANDOM_TRANSITION = 128,
				FLAG_DISABLE_CONDITION = 256,
				FLAG_ALLOW_SELF_TRANSITION_BY_TRANSITION_FROM_ANY_STATE = 512,
				FLAG_IS_GLOBAL_WILDCARD = 1024,
				FLAG_IS_LOCAL_WILDCARD = 2048,
				FLAG_FROM_NESTED_STATE_ID_IS_VALID = 4096,
				FLAG_TO_NESTED_STATE_ID_IS_VALID = 8192,
				FLAG_ABUT_AT_END_OF_FROM_GENERATOR = 16384,
			};

			enum class InternalFlagBits
			{
				FLAG_INTERNAL_IN_TRIGGER_INTERVAL = 1,
				FLAG_INTERNAL_IN_INITIATE_INTERVAL = 2,
			};

			TimeInterval								m_triggerInterval;			// 00
			TimeInterval								m_initiateInterval;			// 10
			hkRefPtr<hkbTransitionEffect>				m_transition;				// 20
			hkRefPtr<hkbCondition>						m_condition;				// 28
			int32_t										m_eventId;					// 30
			int32_t										m_toStateId;				// 34
			int32_t										m_fromNestedStateId;		// 38
			int32_t										m_toNestedStateId;			// 3C
			int16_t										m_priority;					// 40
			stl::enumeration<TransitionFlags, int16_t>	m_flags;					// 42
		};
		static_assert(sizeof(TransitionInfo) == 0x48);

		class TransitionInfoArray : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__TransitionInfoArray;

			~TransitionInfoArray() override;		// 00

			hkArray<TransitionInfo> m_transitions;	// 10
		};
		static_assert(sizeof(TransitionInfoArray) == 0x20);

		class StateInfo : public hkbBindable
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbStateMachine__StateInfo;

			~StateInfo() override;  // 00

			hkArray<hkbStateListener*>		m_listeners;			// 30
			hkRefPtr<EventPropertyArray>	m_enterNotifyEvents;	// 40
			hkRefPtr<EventPropertyArray>	m_exitNotifyEvents;		// 48
			hkRefPtr<TransitionInfoArray>	m_transitions;			// 50
			hkRefPtr<hkbGenerator>			m_generator;			// 58
			hkStringPtr						m_name;					// 60
			int32_t							m_stateId;				// 68
			float							m_probability;			// 6C
			bool							m_enable;				// 70
		};
		static_assert(sizeof(StateInfo) == 0x78);

		struct TransitionInfoReference
		{
			int16_t m_fromStateIndex;		// 00
			int16_t m_transitionIndex;		// 02
			int16_t m_stateMachineId;		// 04
		};
		static_assert(sizeof(TransitionInfoReference) == 0x6);

		struct ActiveTransitionInfo
		{
			hkbTransitionEffect*		m_transitionEffect;						// 00			
			hkbNodeInternalStateInfo*	m_transitionEffectInternalStateInfo;	// 08
			TransitionInfoReference		m_transitionInfoReference;				// 10
			TransitionInfoReference		m_transitionInfoReferenceForTE;			// 16
			int32_t                     m_fromStateId;							// 1C
			int32_t                     m_toStateId;							// 20
			bool						m_isReturnToPreviousState;				// 24
		};
		static_assert(sizeof(ActiveTransitionInfo) == 0x28);

		struct ProspectiveTransitionInfo
		{
			TransitionInfoReference		m_transitionInfoReference;				// 00
			TransitionInfoReference		m_transitionInfoReferenceForTE;			// 06
			int32_t						m_toStateId;							// 0C
		};
		static_assert(sizeof(ProspectiveTransitionInfo) == 0x10);

		struct DelayedTransitionInfo
		{
			ProspectiveTransitionInfo	m_delayedTransition;						// 00
			float                       m_timeDelayed;								// 10
			bool						m_isDelayedTransitionReturnToPreviousState;	// 14
			bool						m_wasInAbutRangeLastFrame;					// 15
		};
		static_assert(sizeof(DelayedTransitionInfo) == 0x18);

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
		hkbEvent														eventToSendWhenStateOrTransitionChanges;  // 048
		hkRefPtr<hkbStateChooser>										startStateChooser;                        // 060
		std::int32_t													startStateID;                             // 068
		std::int32_t													returnToPreviousStateEventID;             // 06C
		std::int32_t													randomTransitionEventID;                  // 070
		std::int32_t													transitionToNextHigherStateEventID;       // 074
		std::int32_t													transitionToNextLowerStateEventID;        // 078
		std::int32_t													syncVariableIndex;                        // 07C
		std::int32_t													currentStateID;                           // 080
		bool															wrapAroundStateID;                        // 084
		std::int8_t														maxSimultaneousTransitions;               // 085
		stl::enumeration<StartStateMode, std::uint8_t>					startStateMode;                           // 086
		stl::enumeration<StateMachineSelfTransitionMode, std::uint8_t>	selfTransitionMode;                       // 087
		bool															isActive;                                 // 088
		hkArray<StateInfo*>												states;                                   // 090
		hkRefPtr<TransitionInfoArray>									wildcardTransitions;                      // 0A0
		hkPointerMap<int, int>*											stateIDToIndexMap;                        // 0A8
		hkArray<ActiveTransitionInfo>									activeTransitions;                        // 0B0
		hkArray<uint8_t>												transitionFlags;                          // 0C0
		hkArray<uint8_t>												wildcardTransitionFlags;                  // 0D0
		hkArray<DelayedTransitionInfo>									delayedTransitions;                       // 0E0
		float															timeInState;                              // 0F0
		float															lastLocalTime;                            // 0F4
		std::int32_t													previousStateID;                          // 0F8
		std::int32_t													nextStartStateIndexOverride;              // 0FC
		bool															stateOrTransitionChanged;                 // 100
		bool															echoNextUpdate;                           // 101
		std::uint16_t													currentStateIndexAndEntered;              // 102
	};
	static_assert(sizeof(hkbStateMachine) == 0x108);
}
