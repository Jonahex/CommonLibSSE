#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/I/IMovementControllerRegisterInterface.h"
#include "RE/M/MovementData.h"

namespace RE
{
	class IMovementControllerDataTracker;
	class IMovementState;
	class MovementAgent;
	class MovementArbiter;

	class MovementControllerAI :
		public IMovementControllerRegisterInterface,  // 000
		public BSIntrusiveRefCounted                  // 008
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerAI;

		~MovementControllerAI() override;  // 00

		// add
		virtual IMovementState* GetMovementState();                                                  // 05
		virtual void            InitDefaultInterfaces();                                             // 06
		virtual void            CalculateMovementData(float deltaTime, MovementData& movementData);  // 07 - Called in Actor::OnFrame
		virtual void            Unk_08(void);                                                        // 08
		virtual void            IsActive();                                                          // 09 - { return 1; } - MovementControllerAI in Actor::CalculateMovementData

		// members
		BSTSmallArray<BSTSmartPointer<MovementArbiter>, 2>               movementArbiters;  // 010
		BSTSmallArray<BSTSmartPointer<MovementAgent>>                    movementAgents;    // 030
		BSTSmallArray<std::pair<BSFixedString, IMovementInterface*>, 11> interfaces;        // 048
		BSReadWriteLock                                                  interfacesLock;    // 108
		std::uint64_t                                                    unk110;            // 110
		IMovementControllerDataTracker*                                  dataTracker;       // 118
	};
	static_assert(sizeof(MovementControllerAI) == 0x120);
}
