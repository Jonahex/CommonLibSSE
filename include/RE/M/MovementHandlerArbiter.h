#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MovementArbiter.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class IMovementHandlerAgent;
	class MovementControllerAI;

	class MovementHandlerArbiter :
		public MovementArbiter  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementHandlerArbiter;

		~MovementHandlerArbiter() override;  // 00

		// override (MovementArbiter)
		const BSFixedString& GetPipelineStageName() const override;                                                  // 01
		const BSFixedString& GetArbiterName() const override;                                                        // 02
		MovementArbiterType  GetType() override;                                                                     // 03
		void                 SetMovementController(MovementControllerAI* controller) override;                       // 04
		void                 Activate() override;                                                                    // 06
		void                 Initialize(BSPathingStreamSimpleBufferRead* buffer) override;                           // 07
		void                 CalculateMovementData(MovementArbitersContext& context) override;                       // 08
		void                 UpdateMovementVirtual(UpdateMovementVirtualContext& context) override;                  // 09
		void                 RemoveMovementController() override;                                                    // 0C
		void                 OnSaveGame(BSPathingStreamWrite* saveBuffer) override;                                  // 0D
		void                 OnLoadGame(BSPathingStreamRead* loadBuffer) override;                                   // 0E
		void                 AddAgent(MovementAgent** agent) override;                                               // 0F
		void                 RemoveAgent(MovementAgent** agent) override;                                            // 10
		void                 ClearAgents() override;                                                                 // 11

		// members
		float                                            currentSpeed;                 // 18
		float                                            currentMovementDirectionZ;    // 1C
		float                                            currentAngleZ;                // 20
		float                                            deltaTime;                    // 24
		float                                            calculatedSpeed;              // 28
		NiPoint3                                         calculatedRotationSpeed;      // 2C
		NiPoint3                                         calculatedAngle;              // 38
		uint32_t                                         ownerFormID;                  // 44
		BSTArray<BSTSmartPointer<IMovementHandlerAgent>> agents;                       // 48
		MovementControllerAI*                            controller;                   // 60
		void*                                            unk68;                        // 68
		void*                                            updateDataSmallDeltaTracker;  // 70
		void*                                            outputDataSmallDeltaTracker;  // 78
	};
	static_assert(sizeof(MovementHandlerArbiter) == 0x80);
}
