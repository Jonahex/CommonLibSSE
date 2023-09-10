#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/M/MovementData.h"
#include "RE/M/MovementHandlerAgent.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class MovementControllerAI;

	class MovementHandlerAgentDirectControl :
		public MovementHandlerAgent  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerAgentDirectControl;

		~MovementHandlerAgentDirectControl() override;  // 00

		// override (MovementAgent)
		const BSFixedString& GetName() const override;                                              // 01
		MovementAgentType    GetType() override;                                                    // 02
		void                 SetMovementController(MovementControllerAI* controller) override;      // 04
		void                 SetProcessingOrder(BSPathingStreamSimpleBufferRead* buffer) override;  // 07
		void                 RemoveMovementController() override;                                   // 0A

		// override (IMovementHandlerAgent)
		const BSFixedString& GetHandlerAgentName() override;                                     // 01
		void                 HandleMovement(float deltaTime, HandlerContext& context) override;  // 02
		void                 Unk_03() override;                                                  // 03

		// members
		MovementData          movementData;                  // 20
		float                 directAngleInputTime;          // 3C
		float                 directSpeedInputTime;          // 40
		float                 directRotationSpeedInputTime;  // 44
		MovementControllerAI* controller;                    // 48
		BSReadWriteLock       lock;                          // 50
		NiPoint3              directAngle;                   // 58
		float                 directSpeed;                   // 64
		NiPoint3              directRotationSpeed;           // 68
	};
	static_assert(sizeof(MovementHandlerAgentDirectControl) == 0x78);
}
