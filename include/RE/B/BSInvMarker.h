#pragma once

#include "RE/N/NiExtraData.h"

namespace RE
{
	class BSInvMarker : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSInvMarker;
		inline static constexpr auto NiRTTI = NiRTTI_BSInvMarker;

		float    zoom;       // 18
		uint16_t rotationX;  // 1C
		uint16_t rotationY;  // 1E
		uint16_t rotationZ;  // 20
	};
}
