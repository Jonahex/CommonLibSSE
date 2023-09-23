#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	struct IdleAnimationData
	{
		NiPoint3      endTranslationLS;        // 00
		NiPoint3      endAngleLS;              // 0C
		NiPoint3      startVelocityLS;         // 18
		NiPoint3      endVelocityLS;           // 24
		NiPoint3      startAngularVelocityLS;  // 30
		NiPoint3      endAngularVelocityLS;    // 3C
		float         clipsLength;             // 48
		float         tweenerStartTime;        // 4C
		float         tweenerEndTime;          // 50
		BSFixedString eventName;               // 58
		bool          unk60;                   // 60
	};
	static_assert(sizeof(IdleAnimationData) == 0x68);
}
