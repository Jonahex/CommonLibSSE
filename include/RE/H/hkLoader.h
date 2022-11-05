#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkLoader : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLoader;

		// override (hkReferencedObject)
		~hkLoader() override;  // 00
		void CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02

		// add
		virtual void Unk_03(void);  // 03
		virtual void Unk_04(void);  // 04
		virtual void Unk_05(void);  // 05
		virtual void Unk_06(void);  // 06
		virtual void Unk_07(void);  // 07
		virtual void Unk_08(void);  // 08
		virtual void Unk_09(void);  // 09
		virtual void Unk_0A(void);  // 0A

		uint64_t    unk10;		// 10
		uint32_t	unk18;		// 18
		uint32_t	unk1c;		// 1C
	};
	static_assert(sizeof(hkLoader) == 0x20);
}
