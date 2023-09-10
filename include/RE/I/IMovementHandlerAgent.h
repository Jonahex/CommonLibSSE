#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IPipelineStageInterface.h"

namespace RE
{
	class MovementControllerContext;
	class MovementData;

	class IMovementHandlerAgent : public IPipelineStageInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementHandlerAgent;

		struct HandlerContext
		{
			MovementControllerContext* controllerContext;    // 00
			MovementData*              handledMovementData;  // 08
		};
		static_assert(sizeof(HandlerContext) == 0x10);

		~IMovementHandlerAgent() override;  // 00

		// add
		virtual const BSFixedString& GetHandlerAgentName() = 0;                                     // 01
		virtual void                 HandleMovement(float deltaTime, HandlerContext& context) = 0;  // 02
		virtual void                 Unk_03() = 0;                                                  // 03 - empty in all implementations, called in MovementHandlerArbiter::Unk_09
	};
	static_assert(sizeof(IMovementHandlerAgent) == 0x8);
}
