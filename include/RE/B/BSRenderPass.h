#pragma once

#include "RE/B/BSShaderProperty.h"

namespace RE
{
	class BSGeometry;
	class BSLight;
	class BSShader;
	class BSShaderProperty;

	class BSRenderPass
	{
	public:
		enum class AccumulationHint : uint8_t
		{
			Unk0 = 0,
			Unk1 = 1,
			Unk2 = 2,
			Unk3 = 3,
			Unk4 = 4,
			Unk5 = 5,
			Unk6 = 6,
			Unk7 = 7,
			Unk8 = 8,
			Unk9 = 9,
			Unk10 = 10,
			Unk11 = 11,
			Unk14 = 14,
			Unk15 = 15,
			Unk16 = 16,
			Clouds = 17,
		};

		struct LODMode
		{
			std::uint8_t index: 7 = 3;
			bool         singleLevel: 1 = false;
		};
		static_assert(sizeof(LODMode) == 0x1);

		static constexpr inline uint8_t MaxShadowLightCount = 4;
		static constexpr inline uint8_t MaxLightCount = 16;

		static BSRenderPass* Make(BSShader* shader, BSShaderProperty* property, BSGeometry* geometry,
			uint32_t technique, uint8_t numLights, BSLight** lights)
		{
			using func_t = decltype(&BSRenderPass::Make);
			REL::Relocation<func_t> func{ RELOCATION_ID(100717, 107497) };
			return func(shader, property, geometry, technique, numLights, lights);
		}

		void Clear()
		{
			using func_t = decltype(&BSRenderPass::Clear);
			REL::Relocation<func_t> func{ RELOCATION_ID(100718, 107498) };
			func(this);
		}

		void SetLights(uint8_t inNumLights, BSLight** lights)
		{
			numLights = inNumLights;
			for (uint8_t lightIndex = 0; lightIndex < numLights; ++lightIndex)
			{
				sceneLights[lightIndex] = lights[lightIndex];
			}
			for (uint8_t lightIndex = numLights; lightIndex < MaxLightCount; ++lightIndex)
			{
				sceneLights[lightIndex] = nullptr;
			}
		}

		// members
		BSShader*                                   shader;                                     // 00
		BSShaderProperty*                           shaderProperty;                             // 08
		BSGeometry*                                 geometry;                                   // 10
		std::uint32_t                               passEnum;                                   // 18
		stl::enumeration<AccumulationHint, uint8_t> accumulationHint = AccumulationHint::Unk0;  // 1C
		std::uint8_t                                extraParam;                                 // 1D
		LODMode                                     LODMode;                                    // 1E
		std::uint8_t                                numLights;                                  // 1F
		std::uint8_t                                numShadowLights;                            // 20
		std::uint8_t                                unk21;                                      // 21
		BSRenderPass*                               next;                                       // 28
		BSRenderPass*                               passGroupNext;                              // 30
		BSLight**                                   sceneLights;                                // 38
		std::uint32_t                               cachePoolId;                                // 40
		std::uint32_t                               pad44;                                      // 44
	};
	static_assert(sizeof(BSRenderPass) == 0x48);
}
