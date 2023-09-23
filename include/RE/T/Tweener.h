#pragma once

#include "RE/N/NiPoint3.h"

namespace RE
{
	struct Tweener
	{
		uint32_t mode;                     // 00
		NiPoint3 targetPositionWS;         // 04
		NiPoint3 targetAngleWS;            // 10
		NiPoint3 targetVelocityWS;         // 1C
		NiPoint3 endTranslationLS;         // 28
		NiPoint3 endAngleLS;               // 34
		NiPoint3 startVelocityLS;          // 40
		NiPoint3 endVelocityLS;            // 4C
		NiPoint3 targetAngularVelocityWS;  // 58
		NiPoint3 startAngularVelocityLS;   // 64
		NiPoint3 endAngularVelocityLS;     // 70
		float    tweenerStartTime;         // 7C
		float    tweenerEndTime;           // 80
		float    clipLength;               // 84
	};
	static_assert(sizeof(Tweener) == 0x88);
}
