#pragma once

#include "RE/I/IMovementParameters.h"

namespace RE
{
	class MovementParameters :
		public IMovementParameters  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementParameters;

		~MovementParameters() override;  // 00

		// override (IMovementParameters)
		float    GetSpeedFactor() override;                          // 01
		float    GetDecelerationRate() override;                     // 02
		float    GetAccelerationRate() override;                     // 03
		float    GetAngularAccelerationRate() override;              // 04
		float    GetRotationSpeedFactor() override;                  // 05
		uint32_t GetNameHash() override;                             // 06
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 07
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 08

		// members
		float speedFactor;              // 10
		float decelerationRate;         // 14
		float accelerationRate;         // 18
		float rotationSpeedFactor;      // 1C
		float angularAccelerationRate;  // 20
	};
	static_assert(sizeof(MovementParameters) == 0x28);
}
