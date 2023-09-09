#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IPipelineStageInterface.h"

namespace RE
{
	class IMovementPlannerAgent : public IPipelineStageInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerAgent;

		~IMovementPlannerAgent() override;  // 00

		// add
		virtual const BSFixedString& GetPlannerAgentName(void) = 0;   // 01
		virtual void                 PlanMovement(void*, void*) = 0;  // 02
		virtual bool                 Unk_03() = 0;                    // 03
	};
	static_assert(sizeof(IMovementPlannerAgent) == 0x8);
}
