#pragma once

#include "RE/H/hkbStateMachine.h"

namespace RE
{
	class hkbStateMachineInternalState : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateMachineInternalState;

		~hkbStateMachineInternalState() override;  // 00

		hkArray<hkbStateMachine::ActiveTransitionInfo>  m_activeTransitions;			// 10
		hkArray<uint8_t>								m_transitionFlags;				// 20
		hkArray<uint8_t>                                m_wildcardTransitionFlags;		// 30
		hkArray<hkbStateMachine::DelayedTransitionInfo> m_delayedTransitions;			// 40
		float											m_timeInState;					// 50
		float                                           m_lastLocalTime;				// 54
		int32_t											m_currentStateId;				// 58
		int32_t                                         m_previousStateId;				// 5C
		int32_t                                         m_nextStartStateIndexOverride;	// 60
		bool											m_stateOrTransitionChanged;		// 64
		bool                                            m_echoNextUpdate;				// 65
	};
	static_assert(sizeof(hkbStateMachineInternalState) == 0x70);
}
