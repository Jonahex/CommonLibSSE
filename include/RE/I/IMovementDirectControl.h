#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementDirectControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementDirectControl;

		~IMovementDirectControl() override;  // 00

		// add
		virtual void EnableDirectControl() = 0;                                                                // 01
		virtual void SetDirectControlAngle(const NiPoint3& angle) = 0;                                         // 02
		virtual void SetDirectControlSpeed(float speed) = 0;                                                   // 03
		virtual void SetDirectControlRotationSpeed(const NiPoint3& rotationSpeed) = 0;                         // 04
		virtual void SetDirectControlAngleAtTime(const NiPoint3& angle, float deltaTime) = 0;                  // 05
		virtual void SetDirectControlSpeedAtTime(float speed, float deltaTime) = 0;                            // 06
		virtual void SetDirectControlRotationSpeedAtTime(const NiPoint3& rotationSpeed, float deltaTime) = 0;  // 07
		virtual void DisableDirectControl() = 0;                                                               // 08
	};
	static_assert(sizeof(IMovementDirectControl) == 0x8);
}
