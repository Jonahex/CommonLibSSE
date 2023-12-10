#pragma once

#include "RE/B/BSTArray.h"

namespace RE
{
	class BSLight;
	class BSShaderProperty;
	class ShadowSceneNode;

	class BSShaderPropertyLightData
	{
	public:
		uint32_t GetLights(BSLight** outLights, uint32_t maxLights,
			uint32_t&         shadowLightCount,
			ShadowSceneNode*  shadowSceneNode,
			BSShaderProperty* property,
			bool              includeShadowLights,
			bool&             shadowDirectionalLight,
			bool              isFirstPerson,
			uint32_t          a9)
		{
			using func_t = decltype(&BSShaderPropertyLightData::GetLights);
			REL::Relocation<func_t> func{ RELOCATION_ID(100997, 107784) };
			return func(this, outLights, maxLights, shadowLightCount, shadowSceneNode, property, includeShadowLights, shadowDirectionalLight, isFirstPerson, a9);
		}

		uint32_t GetAffectingPointShadowLightsCount(BSShaderProperty* property)
		{
			using func_t = decltype(&BSShaderPropertyLightData::GetAffectingPointShadowLightsCount);
			REL::Relocation<func_t> func{ RELOCATION_ID(100994, 107781) };
			return func(this, property);
		}

		// members
		BSTArray<BSLight*> lights;          // 00
		std::int32_t       nextLightIndex;  // 18
		std::uint32_t      flags;           // 1C - 1st bit unkown, i+1-th bit is 1 if object is present in i-th shadowmap of directional light, then 2 bits per each point light's shadowmap
		bool               hasLights;       // 20
	};
	static_assert(sizeof(BSShaderPropertyLightData) == 0x28);
}
