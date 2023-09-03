#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamSimpleBufferRead;
	class BSPathingStreamWrite;
	class IMovementInterface;
	class IMovementState;
	class MovementControllerAI;

	enum class MovementAgentType : uint8_t
	{
		MovementStateFollowPath = 0x0,
		MovementStateTweener = 0x1,
		MovementHandlerAgentAngleController = 0x2,
		MovementHandlerAgentAngleGain = 0x3,
		MovementHandlerAgentAnglePassThrough = 0x4,
		MovementHandlerAgentDirectionPassThrough = 0x5,
		MovementHandlerAgentLargeDeltaIdle = 0x6,
		MovementHandlerAgentSprintPassThrough = 0x7,
		MovementHandlerAgentStrafing = 0x8,
		MovementHandlerAgentTranslationController = 0x9,
		MovementAgentActorState = 0xA,
		MovementAgentActorAvoider = 0xB,
		MovementAgentPathFollowerFlight = 0xC,
		MovementAgentPathFollowerStandard = 0xD,
		MovementAgentPathFollowerVirtual = 0xE,
		MovementPlannerAgentNavmeshBounds = 0xF,
		MovementPathManagerAgentAvoidBox = 0x10,
		MovementPathManagerAgentLoadedAreaMonitor = 0x11,
		MovementPathManagerAgentStaticAvoider = 0x12,
		MovementTweenerAgentFixedDelta = 0x13,
		MovementHandlerAgentDirectControl = 0x80,
		MovementHandlerAgentPlayerControls = 0x81,
		MovementHandlerAgentPlayerControlsActionTrigger = 0x82,
		MovementHandlerAgentSprintActionTrigger = 0x83,
		MovementHandlerAgentStairsHelper = 0x84,
		MovementPlannerAgentDirectControl = 0x85,
		MovementPlannerAgentHorseControls = 0x86,
		MovementPlannerAgentKeepOffset = 0x87,
		MovementPlannerAgentWarp = 0x88,
		MovementTweenerAgentAnimationDriven = 0x89,
		MovementTweenerAgentNodeFollower = 0x8A,
	};

	class MovementAgent :
		public BSIntrusiveRefCounted                  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementAgent;

		~MovementAgent() override;  // 00

		// add
		virtual const BSFixedString& GetName() const = 0;                                          // 01
		virtual MovementAgentType    GetType() = 0;                                                // 02
		virtual IMovementInterface*  GetInterfaceByName(BSFixedString* name) = 0;                  // 03
		virtual void                 SetMovementController(MovementControllerAI* controller);      // 04
		virtual bool                 Unk_04();                                                     // 05
		virtual void                 Activate();                                                   // 06
		virtual void                 SetProcessingOrder(BSPathingStreamSimpleBufferRead* buffer);  // 07
		virtual void                 ResetOwner();                                                 // 08
		virtual void                 Deactivate();                                                 // 09
		virtual void                 RemoveMovementController();                                   // 0A
		virtual void                 OnSaveGame(BSPathingStreamWrite* a2);                         // 0B
		virtual void                 OnLoadGame(BSPathingStreamRead* a2);                          // 0C

		// members
		IMovementState* managedMovementState;  // 10
	};
	static_assert(sizeof(MovementAgent) == 0x18);
}
