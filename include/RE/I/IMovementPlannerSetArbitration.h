#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	class MovementArbitrationMaxWeightParameters;
	class MovementArbitrationMaxWeightPoint;
	class MovementArbitrationVectorAdd;

	class IMovementPlannerSetArbitration : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementPlannerSetArbitration;

		~IMovementPlannerSetArbitration() override;  // 00

		// add
		virtual void  SetMovementArbitrationVectorAdd(const BSTSmartPointer<MovementArbitrationVectorAdd>& arbitration) = 0;                      // 01
		virtual void  SetMovementArbitrationMaxWeightPoint(const BSTSmartPointer<MovementArbitrationMaxWeightPoint>& arbitration) = 0;            // 02
		virtual void  SetMovementArbitrationMaxWeightParameters(const BSTSmartPointer<MovementArbitrationMaxWeightParameters>& arbitration) = 0;  // 03
		virtual void  ResetMovementParameters() = 0;                                                                                              // 04
		virtual bool  AreMovementParametersInitialized() = 0;                                                                                     // 05
		virtual float GetTimeBlocked() = 0;                                                                                                       // 06
	};
	static_assert(sizeof(IMovementPlannerSetArbitration) == 0x8);
}
