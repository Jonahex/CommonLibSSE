#pragma once

#include "RE/B/BSTHashMap.h"
#include "RE/B/BSFixedString.h"
#include "RE/H/hkLoader.h"

namespace RE
{
	class BShkbHkxDB
	{
	public:
		class DBData : public hkLoader
		{
		public:
			inline static constexpr auto RTTI = RTTI_BShkbHkxDB__DBData;

			// override (hkLoader)
			~DBData() override;			// 00

			// add
			virtual void Unk_0B(void);  // 0B - { return; }
			virtual void Unk_0C(void);  // 0C - { return; }
			virtual void Unk_0D(void);  // 0D
			virtual void Unk_0E(void);  // 0E - { return; }

			uint64_t unk20;  // 20
		};
		static_assert(sizeof(DBData) == 0x28);

		class ProjectDBData : public DBData
		{
		public:
			inline static constexpr auto RTTI = RTTI_BShkbHkxDB__ProjectDBData;

			// override (DBData)
			~ProjectDBData() override;   // 00
			void Unk_0B(void) override;  // 0B - { return; }

			uint64_t                       unk28;						// 28
			uint32_t                       unk30;						// 30
			uint64_t                       unk38;						// 38
			uint64_t                       unk40;						// 40
			uint32_t                       unk48;						// 48
			uint32_t                       pad4C;						// 4C
			uint32_t                       unk50;						// 50
			uint64_t                       unk58;						// 58
			uint64_t                       unk60;						// 60
			uint32_t                       unk68;						// 68
			BSTHashMap<BSFixedString, int> variables;					// 70
			BSTHashMap<BSFixedString, int> events;						// A0
			uint64_t                       unkD0;						// D0
			uint32_t                       unkD8;						// D8
			uint32_t                       padDC;						// DC
			uint32_t                       unkE0;						// E0
			uint64_t                       unkE8;						// E8
			uint32_t                       unkF0;						// F0
			uint32_t                       padF4;						// F4
			uint64_t                       unkF8;						// F8
			BSTSet<BSFixedString>          synchronizedClipGenerators;	// 100
			uint64_t                       unk130;						// 130
			uint32_t                       unk138;						// 138
			uint32_t                       pad13C;						// 13C
			uint32_t                       unk140;						// 140
			uint64_t                       unk148;						// 148
			uint64_t                       unk150;						// 150
			uint64_t                       unk158;						// 158
			uint64_t                       unk160;						// 160
			uint32_t                       unk168;						// 168
			uint64_t                       unk170;						// 170
			uint64_t                       unk178;						// 178
		};
		static_assert(sizeof(ProjectDBData) == 0x180);
	};
}
