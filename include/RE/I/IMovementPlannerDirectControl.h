#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementPlannerDirectControl : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerDirectControl;

		~IMovementPlannerDirectControl() override;  // 00

		// add
		virtual void EnablePlannerDirectControl() = 0;                                       // 01
		virtual void SetPlannerDirectControlMovementVectorAngle(const NiPoint3& angle) = 0;  // 02
		virtual void SetPlannerDirectControlMovementVectorSpeed(float speed) = 0;            // 03
		virtual void SetPlannerDirectControlMovementAngle(const NiPoint3& angle) = 0;        // 04
		virtual void DisablePlannerDirectControl() = 0;                                      // 05
	};
	static_assert(sizeof(IMovementPlannerDirectControl) == 0x8);
}
