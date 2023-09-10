#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementMotionDrivenControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementMotionDrivenControl;

		~IMovementMotionDrivenControl() override;  // 00

		// add
		virtual void InitWithHighProcessLevel() = 0;     // 01
		virtual void InitWithoutHighProcessLevel() = 0;  // 02
		virtual void StartAnimationDriven() = 0;         // 03
		virtual void StartMotionDriven() = 0;            // 04
		virtual void StartAllowRotation() = 0;           // 05
		virtual bool IsMotionDriven() = 0;               // 06
		virtual bool IsNonMotionDriven() = 0;            // 07
		virtual bool IsAllowRotation() = 0;              // 08
	};
	static_assert(sizeof(IMovementMotionDrivenControl) == 0x8);
}
