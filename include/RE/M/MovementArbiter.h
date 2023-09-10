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
	class MovementAgent;
	class MovementArbitersContext;
	class MovementControllerAI;

	enum class MovementArbiterType : uint8_t
	{
		Handler = 0x0,
		PathManager = 0x1,
		Planner = 0x2,
		PostUpdate = 0x3,
		Tweener = 0x4,
	};

	class MovementArbiter :
		public BSIntrusiveRefCounted  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementArbiter;

		virtual ~MovementArbiter();  // 00

		// add
		virtual const BSFixedString& GetPipelineStageName() const = 0;                             // 01
		virtual const BSFixedString& GetArbiterName() const = 0;                                   // 02
		virtual MovementArbiterType  GetType() = 0;                                                // 03
		virtual void                 SetMovementController(MovementControllerAI* controller);      // 04
		virtual void                 Unk_05();                                                     // 05
		virtual void                 Activate();                                                   // 06
		virtual void                 SetProcessingOrder(BSPathingStreamSimpleBufferRead* buffer);  // 07
		virtual void                 CalculateMovementData(MovementArbitersContext& context) = 0;  // 08
		virtual void                 Unk_09(MovementArbitersContext& context) = 0;                 // 09
		virtual bool                 Unk_0A();                                                     // 0A
		virtual bool                 Unk_0B();                                                     // 0B
		virtual void                 RemoveMovementController();                                   // 0C
		virtual void                 OnSaveGame(BSPathingStreamWrite* saveBuffer);                 // 0D
		virtual void                 OnLoadGame(BSPathingStreamRead* loadBuffer);                  // 0E
		virtual void                 AddAgent(MovementAgent** agent);                              // 0F
		virtual void                 RemoveAgent(MovementAgent** agent);                           // 10
		virtual void                 ClearAgents();                                                // 11

		// members
		IMovementState* managedMovementState;  // 10
	};
	static_assert(sizeof(MovementArbiter) == 0x18);
}
