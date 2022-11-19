#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/E/ExtraDataTypes.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class ExtraCellWaterEnvMap : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCellWaterEnvMap;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCellWaterEnvMap;

		// override (BSExtraData)
		~ExtraCellWaterEnvMap() override = default;							// 00
		ExtraDataType GetType() const override								// 01
		{
			return EXTRADATATYPE;
		}
		bool IsNotEqual(const BSExtraData* a_rhs) const override			// 02
		{
			return waterEnvMap.textureName != static_cast<const ExtraCellWaterEnvMap*>(a_rhs)->waterEnvMap.textureName;
		}

		// members
		TESTexture waterEnvMap;  // 10
	};
	static_assert(sizeof(ExtraCellWaterEnvMap) == 0x20);
}
