#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiSourceTexture.h"

namespace RE
{
	namespace BSGraphics
	{
		class State
		{
		public:
			[[nodiscard]] static State* GetSingleton()
			{
				REL::Relocation<State*> singleton{ RELOCATION_ID(524998, 411479) };
				return singleton.get();
			}

			// members
			NiPointer<NiSourceTexture> defaultTextureProjNoiseMap;                  // 000
			NiPointer<NiSourceTexture> defaultTextureProjDiffuseMap;                // 008
			NiPointer<NiSourceTexture> defaultTextureProjNormalMap;                 // 010
			NiPointer<NiSourceTexture> defaultTextureProjNormalDetailMap;           // 018
			uint32_t                   unk20;                                       // 020
			uint32_t                   screenWidth;                                 // 024
			uint32_t                   screenHeight;                                // 028
			uint32_t                   frameBufferViewport[2];                      // 02C
			uint32_t                   unk34;                                       // 034
			uint32_t                   unk38;                                       // 038
			uint32_t                   unk3C;                                       // 03C
			uint32_t                   unk40;                                       // 040
			uint32_t                   unk44;                                       // 044
			uint32_t                   unk48;                                       // 048
			uint32_t                   uiFrameCount;                                // 04C
			bool                       insideFrame;                                 // 050
			bool                       letterbox;                                   // 051
			bool                       unk52;                                       // 052
			bool                       compiledShaderThisFrame;                     // 053
			bool                       useEarlyZ;                                   // 054
			bool                       unk55;                                       // 055
#ifdef SKYRIM_SUPPORT_AE
			bool                       unk56;                                       // 056
			bool                       doubleDynamicResolutionAdjustmentFrequency;  // 057
			bool                       unk58;                                       // 058
#endif
			NiPointer<NiSourceTexture> defaultTextureBlack;                         // 060
			NiPointer<NiSourceTexture> defaultTextureWhite;                         // 068
			NiPointer<NiSourceTexture> defaultTextureGrey;                          // 070
			NiPointer<NiSourceTexture> defaultHeightMap;                            // 078
			NiPointer<NiSourceTexture> defaultReflectionCubeMap;                    // 080
			NiPointer<NiSourceTexture> defaultFaceDetailMap;                        // 088
			NiPointer<NiSourceTexture> defaultTexEffectMap;                         // 090
			NiPointer<NiSourceTexture> defaultTextureNormalMap;                     // 098
			NiPointer<NiSourceTexture> defaultTextureDitherNoiseMap;                // 0A0
			BSTArray<void*>            cameraDataCacheA;                            // 0A8
			uint32_t                   unkC0;                                       // 0C0
			float                      haltonSequence[2][8];                        // 0C4
			float                      dynamicResolutionWidthRatio;                 // 104
			float                      dynamicResolutionHeightRatio;                // 108
			float                      dynamicResolutionPreviousWidthRatio;         // 10C
			float                      dynamicResolutionPreviousHeightRatio;        // 110
			uint32_t                   uiDynamicResolutionIncreaseFrameWaited;      // 114
			uint32_t                   dynamicResolutionLock;                       // 118
			bool                       canIncreaseDynamicResolution;                // 11C
			bool                       canDecreaseDynamicResolution;                // 11D
			bool                       canChangeDynamicResolution;                  // 11E
		};
#ifdef SKYRIM_SUPPORT_AE
		static_assert(sizeof(State) == 0x120);
#else
		static_assert(sizeof(State) == 0x118);
#endif
	}
}
