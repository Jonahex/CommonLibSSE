#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/I/IMovementParameters.h"

namespace RE
{
	class MovementParametersFixed :
		public IMovementParameters  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_MovementParametersFixed;

		~MovementParametersFixed() override;  // 00

		// override (IMovementParameters)
		float    GetNormalizedSpeed() override;                      // 01
		float    GetAccelerationRate() override;                     // 02
		float    GetDecelerationRate() override;                     // 03
		float    GetAngularAccelerationRate() override;              // 04
		float    GetNormalizedRotationSpeed() override;              // 05
		uint32_t GetNameHash() override;                             // 06
		void     OnSaveGame(BSPathingStreamWrite* stream) override;  // 07
		void     OnLoadGame(BSPathingStreamRead* stream) override;   // 08

		// members
		float       normalizedSpeed;          // 10
		float       accelerationRate;         // 14
		float       decelerationRate;         // 18
		float       normalizedRotationSpeed;  // 1C
		float       angularAccelerationRate;  // 20
		ActorHandle actorHandle;              // 24
	};
	static_assert(sizeof(MovementParametersFixed) == 0x28);
}
