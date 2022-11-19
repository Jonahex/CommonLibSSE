#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class TESImageSpace;

	class ExtraCellImageSpace : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCellImageSpace;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCellImageSpace;

		// override (BSExtraData)
		~ExtraCellImageSpace() = default;							// 00
		ExtraDataType GetType() const override						// 01
		{
			return EXTRADATATYPE;
		}
		bool IsNotEqual(const BSExtraData* a_rhs) const override	// 02
		{
			return imageSpace != static_cast<const ExtraCellImageSpace*>(a_rhs)->imageSpace;
		}

		// members
		TESImageSpace* imageSpace = nullptr;  // 10
	};
	static_assert(sizeof(ExtraCellImageSpace) == 0x18);
}
