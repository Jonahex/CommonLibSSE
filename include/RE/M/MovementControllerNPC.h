#pragma once

#include "RE/I/IAnimationSetCallbackFunctor.h"
#include "RE/I/IMovementDirectControl.h"
#include "RE/I/IMovementMessageInterface.h"
#include "RE/I/IMovementMotionDrivenControl.h"
#include "RE/I/IMovementPlannerDirectControl.h"
#include "RE/I/IMovementSelectIdle.h"
#include "RE/M/MovementControllerAI.h"
#include "RE/W/WarpPoint.h"

namespace RE
{
	class MovementMessage;

	class MovementControllerNPC :
		public MovementControllerAI,           // 000
		public IMovementMessageInterface,      // 120
		public IMovementMotionDrivenControl,   // 128
		public IMovementSelectIdle,            // 130
		public IMovementDirectControl,         // 138
		public IMovementPlannerDirectControl,  // 140
		public IAnimationSetCallbackFunctor    // 148
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementControllerNPC;

		enum class State
		{
			HighLevelAnimationDriven = 0x0,
			HighLevelMotionDrivenControlsDriven = 0x1,
			HighLevelMotionDriven = 0x2,
			HighLevelMotionDrivenFlying = 0x3,
			HighLevelAllowRotation = 0x4,
			HighLevelAllowRotationControlsDriven = 0x5,
			NodeFollower = 0x6,
			HighLevelMotionDrivenDirectControl = 0x7,
			HighLevelMotionDrivenPlannerDirectControl = 0x8,
			HighLevelAllowRotationDirectControl = 0x9,
			LowLevelMotionDrivenGround = 0xA,
			LowLevelMotionDrivenFlying = 0xB,
			HighLevelMotionDrivenStaticPath = 0xC,
			HighLevelMotionDrivenKeepOffsetFromActor = 0xD,
			HighLevelMotionDrivenControlsDrivenMount = 0xE,
		};

		~MovementControllerNPC() override;  // 00

		// override (MovementControllerAI)
		void InitDefaultInterfaces() override;  // 06
		void IsActive() override;               // 09

		// override (IMovementMessageInterface)
		void EnqueueWarp(const PathingPoint& pathingPoint, const NiPoint3& angle) override;        // 01
		void EnqueueMessage(const BSTSmartPointer<MovementMessage>& message) override;             // 02
		void ImmediatelyProcessMessage(const BSTSmartPointer<MovementMessage>& message) override;  // 03

		// override (IMovementMotionDrivenControl)
		void InitWithHighProcessLevel() override;     // 01
		void InitWithoutHighProcessLevel() override;  // 02
		void StartAnimationDriven() override;         // 03
		void StartMotionDriven() override;            // 04
		void StartAllowRotation() override;           // 05
		bool IsMotionDriven() override;               // 06
		bool IsNonMotionDriven() override;            // 07
		bool IsAllowRotation() override;              // 08

		// override (IMovementSelectIdle)
		bool SelectIdle(const PathingParameters& pathingParameters, ISelectIdleFilter* selectIdleFilter, IdleAnimationData& outIdleData) override;  // 01
		bool EstimateRotationVelocityInIdle(const IdleAnimationData& idleData, NiPoint3& outRotationVelocity) const override;                       // 02
		void PlayIdle(const BSFixedString& eventName, const Tweener& tweener, IMovementPlayIdleResult*& playIdleResult) override;                   // 03
		void ClearIdles() override;                                                                                                                 // 04
		bool HasIdleToPlay() const override;                                                                                                        // 05

		// override (IMovementDirectControl)
		void EnableDirectControl() override;                                                                // 01
		void SetDirectControlAngle(const NiPoint3& angle) override;                                         // 02
		void SetDirectControlSpeed(float speed) override;                                                   // 03
		void SetDirectControlRotationSpeed(const NiPoint3& rotationSpeed) override;                         // 04
		void SetDirectControlAngleAtTime(const NiPoint3& angle, float deltaTime) override;                  // 05
		void SetDirectControlSpeedAtTime(float speed, float deltaTime) override;                            // 06
		void SetDirectControlRotationSpeedAtTime(const NiPoint3& rotationSpeed, float deltaTime) override;  // 07
		void DisableDirectControl() override;                                                               // 08

		// override (IMovementPlannerDirectControl)
		void EnablePlannerDirectControl() override;                                       // 01
		void SetPlannerDirectControlMovementVectorAngle(const NiPoint3& angle) override;  // 02
		void SetPlannerDirectControlMovementVectorSpeed(float speed) override;            // 03
		void SetPlannerDirectControlMovementAngle(const NiPoint3& angle) override;        // 04
		void DisablePlannerDirectControl() override;                                      // 05

		// add
		virtual void SetIsSprinting(bool isSprinting);           // 0A
		virtual bool GetIsSprinting() const;                     // 0B
		virtual void SetAIDriven();                              // 0C
		virtual void SetControlsDriven();                        // 0D
		virtual bool IsAIDriven();                               // 0E
		virtual bool IsControlsDriven();                         // 0F
		virtual void SetNodeFollowerState();                     // 10
		virtual void SetFlying(bool isFlying);                   // 11
		virtual void OnSaveGame(BGSSaveFormBuffer* buffer);      // 12
		virtual void OnLoadGame(BGSLoadGameBuffer* buffer);      // 13
		virtual void OnMessage(const MovementMessage& message);  // 14

		// members
		BSSpinLock                       messageQueueLock;             // 150
		BSTArray<MovementMessage*>       messageQueue;                 // 158
		BSTArray<WarpPoint>              warpQueue;                    // 170
		BSTArray<void*>                  unk188;                       // 188
		BSSpinLock                       unk1A0;                       // 1A0
		std::uint64_t                    unk1A8;                       // 1A8
		BSTSmartPointer<MovementMessage> playIdleMessage;              // 1B0
		Actor*                           owner;                        // 1B8
		State                            currentState;                 // 1C0
		bool                             isFlying;                     // 1C4
		bool                             isControlsDriven;             // 1C5
		bool                             directControlEnabled;         // 1C6
		bool                             plannerDirectControlEnabled;  // 1C7
		bool                             isLowLevel;                   // 1C8
		bool                             isHighLevel;                  // 1C9
		bool                             isStaticPath;                 // 1CA
		bool                             keepOffsetFromActor;          // 1CB
	};
	static_assert(sizeof(MovementControllerNPC) == 0x1D0);
}
