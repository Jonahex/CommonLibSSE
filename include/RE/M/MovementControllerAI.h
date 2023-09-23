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

		template <typename T>
		struct MovementPtr
		{
			T* Get() const
			{
				return reinterpret_cast<T*>(reinterpret_cast<void*>(data & ~1ui64));
			}

			uint64_t data;
		};

		// add
		virtual IMovementState* GetMovementState();                                                        // 05
		virtual void            InitDefaultInterfaces();                                                   // 06
		virtual void            CalculateMovementData(float deltaTime, MovementData& movementData);        // 07 - Called in Actor::OnFrame
		virtual void            UpdateMovementVirtual(float deltaTime, BSTArray<BSFixedString>& context);  // 08
		virtual void            IsActive();                                                                // 09 - { return 1; } - MovementControllerAI in Actor::CalculateMovementData

		// members
		BSTSmallArray<MovementPtr<MovementArbiter>, 2>                   movementArbiters;  // 010
		BSTSmallArray<MovementPtr<MovementAgent>>                        movementAgents;    // 030
		BSTSmallArray<std::pair<BSFixedString, IMovementInterface*>, 11> interfaces;        // 048
		BSReadWriteLock                                                  interfacesLock;    // 108
		std::uint64_t                                                    unk110;            // 110
		IMovementControllerDataTracker*                                  dataTracker;       // 118
	};
	static_assert(sizeof(MovementControllerAI) == 0x120);
}
