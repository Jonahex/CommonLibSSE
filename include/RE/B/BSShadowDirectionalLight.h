#pragma once

#include "RE/B/BSShadowLight.h"

namespace RE
{
	class BSShadowDirectionalLight : public BSShadowLight
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShadowDirectionalLight;

		~BSShadowDirectionalLight() override;  // 00

		// members
		uint64_t        unk560;  // 560
		uint64_t        unk568;  // 568
		uint64_t        unk570;  // 570
		uint64_t        unk578;  // 578
		BSTArray<void*> unk580;  // 580
		uint64_t        unk598;  // 598
		uint64_t        unk5A0;  // 5A0
		uint64_t        unk5A8;  // 5A8
		uint64_t        unk5B0;  // 5B0
	};
	static_assert(sizeof(BSShadowDirectionalLight) == 0x5B8);
}
