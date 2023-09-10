#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;

	class IMovementParameters : public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementParameters;

		virtual ~IMovementParameters();  // 00

		// add
		virtual float    GetSpeedFactor() = 0;                          // 01
		virtual float    GetDecelerationRate() = 0;                     // 02
		virtual float    GetAccelerationRate() = 0;                     // 03
		virtual float    GetAngularAccelerationRate() = 0;              // 04
		virtual float    GetRotationSpeedFactor() = 0;                  // 05
		virtual uint32_t GetNameHash() = 0;                             // 06
		virtual void     OnSaveGame(BSPathingStreamWrite* stream) = 0;  // 07
		virtual void     OnLoadGame(BSPathingStreamRead* stream) = 0;   // 08
	};
	static_assert(sizeof(IMovementParameters) == 0x10);
}
