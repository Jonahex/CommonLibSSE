#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/N/NiTArray.h"
#include "RE/T/TESImageSpace.h"

namespace RE
{
	class BSShader;
	class ImageSpaceEffect;

	class ImageSpaceEffectManager : public BSTSingletonExplicit<ImageSpaceEffectManager>
	{
	public:
		enum class EffectType
		{
			WorldMap = 0,									// ImageSpaceEffectWorldMap
			Refraction = 1,									// ImageSpaceEffectRefraction
			ISFXAA = 2,										// BSImagespaceShaderFXAA
			DepthOfField = 3,								// ImageSpaceEffectDepthOfField
			RadialBlur = 5,									// ImageSpaceEffectRadialBlur
			FullScreenBlur = 6,								// ImageSpaceEffectFullScreenBlur
			GetHit = 7,										// ImageSpaceEffectGetHit
			Map = 8,										// ImageSpaceEffectMap
			Blur3 = 9,										// ImageSpaceEffectBlur
			Blur5 = 10,										// ImageSpaceEffectBlur
			Blur7 = 11,										// ImageSpaceEffectBlur
			Blur9 = 12,										// ImageSpaceEffectBlur
			Blur11 = 13,                                    // ImageSpaceEffectBlur
			Blur13 = 14,                                    // ImageSpaceEffectBlur
			Blur15 = 15,                                    // ImageSpaceEffectBlur
			BlurNonHDR3 = 16,								// ImageSpaceEffectBlur
			BlurNonHDR5 = 17,								// ImageSpaceEffectBlur
			BlurNonHDR7 = 18,								// ImageSpaceEffectBlur
			BlurNonHDR9 = 19,								// ImageSpaceEffectBlur
			BlurNonHDR11 = 20,                              // ImageSpaceEffectBlur
			BlurNonHDR13 = 21,                              // ImageSpaceEffectBlur
			BlurNonHDR15 = 22,                              // ImageSpaceEffectBlur
			BlurBrightPass3 = 23,							// ImageSpaceEffectBlur
			BlurBrightPass5 = 24,							// ImageSpaceEffectBlur
			BlurBrightPass7 = 25,							// ImageSpaceEffectBlur
			BlurBrightPass9 = 26,							// ImageSpaceEffectBlur
			BlurBrightPass11 = 27,                          // ImageSpaceEffectBlur
			BlurBrightPass13 = 28,                          // ImageSpaceEffectBlur
			BlurBrightPass15 = 29,                          // ImageSpaceEffectBlur
			HDR = 30,										// ImageSpaceEffectHDR
			WaterDisplacement = 31,							// ImageSpaceEffectWaterDisplacement
			VolumetricLighting = 32,						// ImageSpaceEffectVolumetricLighting
			Noise = 33,										// ImageSpaceEffectNoise
			ISCopy = 34,									// BSImagespaceShaderCopy
			ISCopyDynamicFetchDisabled = 35,				// BSImagespaceShaderCopyDynamicFetchDisabled
			ISCopyScaleBias = 36,							// BSImagespaceShaderCopyScaleBias
			ISCopyCustomViewport = 37,						// BSImagespaceShaderCopyCustomViewport
			ISCopyGrayScale = 38,							// BSImagespaceShaderGreyScale
			ISRefraction = 39,								// BSImagespaceShaderRefraction
			ISDoubleVision = 40,							// BSImagespaceShaderDoubleVision
			ISCopyTextureMask = 41,							// BSImagespaceShaderTextureMask
			ISMap = 42,										// BSImagespaceShaderMap
			ISWorldMap = 43,								// BSImagespaceShaderWorldMap
			ISWorldMapNoSkyBlur = 44,						// BSImagespaceShaderWorldMapNoSkyBlur
			ISDepthOfField = 45,							// BSImagespaceShaderDepthOfField
			ISDepthOfFieldFogged = 46,						// BSImagespaceShaderDepthOfFieldFogged
			ISDepthOfFieldMaskedFogged = 47,				// BSImagespaceShaderDepthOfFieldMaskedFogged
			ISDistantBlur = 49,								// BSImagespaceShaderDistantBlur
			ISDistantBlurFogged = 50,						// BSImagespaceShaderDistantBlurFogged
			ISDistantBlurMaskedFogged = 51,					// BSImagespaceShaderDistantBlurMaskedFogged
			ISRadialBlur = 52,								// BSImagespaceShaderRadialBlur
			ISRadialBlurMedium = 53,						// BSImagespaceShaderRadialBlurMedium
			ISRadialBlurHigh = 54,							// BSImagespaceShaderRadialBlurHigh
			ISHDRTonemapBlendCinematic = 55,				// BSImagespaceShaderHDRTonemapBlendCinematic
			ISHDRTonemapBlendCinematicFade = 56,			// BSImagespaceShaderHDRTonemapBlendCinematicFade
			ISHDRDownSample16 = 57,							// BSImagespaceShaderHDRDownSample16
			ISHDRDownSample4 = 58,							// BSImagespaceShaderHDRDownSample4
			ISHDRDownSample16Lum = 59,						// BSImagespaceShaderHDRDownSample16Lum
			ISHDRDownSample4RGB2Lum = 60,					// BSImagespaceShaderHDRDownSample4RGB2Lum
			ISHDRDownSample4LumClamp = 61,					// BSImagespaceShaderHDRDownSample4LumClamp
			ISHDRDownSample4LightAdapt = 62,				// BSImagespaceShaderHDRDownSample4LightAdapt
			ISHDRDownSample16LumClamp = 63,					// BSImagespaceShaderHDRDownSample16LumClamp
			ISHDRDownSample16LightAdapt = 64,				// BSImagespaceShaderHDRDownSample16LightAdapt
			ISBlur3 = 65,									// BSImagespaceShaderBlur3
			ISBlur5 = 66,									// BSImagespaceShaderBlur5
			ISBlur7 = 67,									// BSImagespaceShaderBlur7
			ISBlur9 = 68,									// BSImagespaceShaderBlur9
			ISBlur11 = 69,									// BSImagespaceShaderBlur11
			ISBlur13 = 70,									// BSImagespaceShaderBlur13
			ISBlur15 = 71,									// BSImagespaceShaderBlur15
			ISNonHDRBlur3 = 72,								// BSImagespaceShaderNonHDRBlur3
			ISNonHDRBlur5 = 73,								// BSImagespaceShaderNonHDRBlur5
			ISNonHDRBlur7 = 74,								// BSImagespaceShaderNonHDRBlur7
			ISNonHDRBlur9 = 75,								// BSImagespaceShaderNonHDRBlur9
			ISNonHDRBlur11 = 76,							// BSImagespaceShaderNonHDRBlur11
			ISNonHDRBlur13 = 77,							// BSImagespaceShaderNonHDRBlur13
			ISNonHDRBlur15 = 78,							// BSImagespaceShaderNonHDRBlur15
			ISBrightPassBlur3 = 79,							// BSImagespaceShaderBrightPassBlur3
			ISBrightPassBlur5 = 80,							// BSImagespaceShaderBrightPassBlur5
			ISBrightPassBlur7 = 81,							// BSImagespaceShaderBrightPassBlur7
			ISBrightPassBlur9 = 82,							// BSImagespaceShaderBrightPassBlur9
			ISBrightPassBlur11 = 83,						// BSImagespaceShaderBrightPassBlur11
			ISBrightPassBlur13 = 84,						// BSImagespaceShaderBrightPassBlur13
			ISBrightPassBlur15 = 85,						// BSImagespaceShaderBrightPassBlur15
			ISWaterDisplacementClearSimulation = 86,		// BSImagespaceShaderWaterDisplacementClearSimulation
			ISWaterDisplacementTexOffset = 87,				// BSImagespaceShaderWaterDisplacementTexOffset
			ISWaterDisplacementWadingRipple = 88,			// BSImagespaceShaderWaterDisplacementWadingRipple
			ISWaterDisplacementRainRipple = 89,				// BSImagespaceShaderWaterDisplacementRainRipple
			ISWaterWadingHeightmap = 90,					// BSImagespaceShaderWaterWadingHeightmap
			ISWaterRainHeightmap = 91,						// BSImagespaceShaderWaterRainHeightmap
			ISWaterBlendHeightmaps = 92,					// BSImagespaceShaderWaterBlendHeightmaps
			ISWaterSmoothHeightmap = 93,					// BSImagespaceShaderWaterSmoothHeightmap
			ISWaterDisplacementNormals = 94,				// BSImagespaceShaderWaterDisplacementNormals
			ISNoiseScrollAndBlend = 95,						// BSImagespaceShaderNoiseScrollAndBlend
			ISNoiseNormalmap = 96,							// BSImagespaceShaderNoiseNormalmap
			ISVolumetricLighting = 97,						// BSImagespaceShaderVolumetricLighting
			ISLocalMap = 98,								// BSImagespaceShaderLocalMap
			ISAlphaBlend = 99,								// BSImagespaceShaderAlphaBlend
			ISLensFlare = 100,								// BSImagespaceShaderLensFlare
			ISLensFlareVisibility = 101,					// BSImagespaceShaderLensFlareVisibility
			ISApplyReflections = 102,						// BSImagespaceShaderApplyReflections
			ISApplyVolumetricLighting = 103,				// BSImagespaceShaderISApplyVolumetricLighting
			ISBasicCopy = 104,								// BSImagespaceShaderISBasicCopy
			ISBlur = 105,									// BSImagespaceShaderISBlur
			ISVolumetricLightingBlurHCS = 106,				// BSImagespaceShaderISVolumetricLightingBlurHCS
			ISVolumetricLightingBlurVCS = 107,				// BSImagespaceShaderISVolumetricLightingBlurVCS
			ISReflectionBlurHCS = 108,						// BSImagespaceShaderReflectionBlurHCS
			ISReflectionBlurVCS = 109,						// BSImagespaceShaderReflectionBlurVCS
			ISParallaxMaskBlurHCS = 110,					// BSImagespaceShaderISParallaxMaskBlurHCS
			ISParallaxMaskBlurVCS = 111,					// BSImagespaceShaderISParallaxMaskBlurVCS
			ISDepthOfFieldBlurHCS = 112,					// BSImagespaceShaderISDepthOfFieldBlurHCS
			ISDepthOfFieldBlurVCS = 113,					// BSImagespaceShaderISDepthOfFieldBlurVCS
			ISCompositeVolumetricLighting = 114,			// BSImagespaceShaderISCompositeVolumetricLighting
			ISCompositeLensFlare = 115,						// BSImagespaceShaderISCompositeLensFlare
			ISCompositeLensFlareVolumetricLighting = 116,	// BSImagespaceShaderISCompositeLensFlareVolumetricLighting
			ISCopySubRegionCS = 117,						// BSImagespaceShaderISCopySubRegionCS
			ISDebugSnow = 118,								// BSImagespaceShaderISDebugSnow
			ISDownsample = 119,								// BSImagespaceShaderISDownsample
			ISDownsampleIgnoreBrightest = 120,				// BSImagespaceShaderISDownsampleIgnoreBrightest
			ISDownsampleCS = 121,							// BSImagespaceShaderISDownsampleCS
			ISDownsampleIgnoreBrightestCS = 122,			// BSImagespaceShaderISDownsampleIgnoreBrightestCS
			ISExp = 123,									// BSImagespaceShaderISExp
			ISIBLensFlares = 124,							// BSImagespaceShaderISIBLensFlares
			ISLightingComposite = 125,						// BSImagespaceShaderISLightingComposite
			ISLightingCompositeNoDirectionalLight = 126,	// BSImagespaceShaderISLightingCompositeNoDirectionalLight
			ISLightingCompositeMenu = 127,					// BSImagespaceShaderISLightingCompositeMenu
			ISPerlinNoiseCS = 128,							// BSImagespaceShaderISPerlinNoiseCS
			ISPerlinNoise2DCS = 129,						// BSImagespaceShaderISPerlinNoise2DCS
			ISReflectionsRayTracing = 130,					// BSImagespaceShaderReflectionsRayTracing
			ISReflectionsDebugSpecMask = 131,				// BSImagespaceShaderReflectionsDebugSpecMask
			ISSAOBlurH = 132,								// BSImagespaceShaderISSAOBlurH
			ISSAOBlurV = 133,								// BSImagespaceShaderISSAOBlurV
			ISSAOBlurHCS = 134,								// BSImagespaceShaderISSAOBlurHCS
			ISSAOBlurVCS = 135,								// BSImagespaceShaderISSAOBlurVCS
			ISSAOCameraZ = 136,								// BSImagespaceShaderISSAOCameraZ
			ISSAOCameraZAndMipsCS = 137,					// BSImagespaceShaderISSAOCameraZAndMipsCS
			ISSAOCompositeSAO = 138,						// BSImagespaceShaderISSAOCompositeSAO
			ISSAOCompositeFog = 139,						// BSImagespaceShaderISSAOCompositeFog
			ISSAOCompositeSAOFog = 140,						// BSImagespaceShaderISSAOCompositeSAOFog
			ISMinify = 141,									// BSImagespaceShaderISMinify
			ISMinifyContrast = 142,							// BSImagespaceShaderISMinifyContrast
			ISSAORawAO = 143,								// BSImagespaceShaderISSAORawAO
			ISSAORawAONoTemporal = 144,						// BSImagespaceShaderISSAORawAONoTemporal
			ISSAORawAOCS = 145,								// BSImagespaceShaderISSAORawAOCS
			ISSILComposite = 146,							// BSImagespaceShaderISSILComposite
			ISSILRawInd = 147,								// BSImagespaceShaderISSILRawInd
			ISSimpleColor = 148,							// BSImagespaceShaderISSimpleColor
			ISDisplayDepth = 149,							// BSImagespaceShaderISDisplayDepth
			ISSnowSSS = 150,								// BSImagespaceShaderISSnowSSS
			ISTemporalAA = 151,								// BSImagespaceShaderISTemporalAA
			ISTemporalAA_UI = 152,							// BSImagespaceShaderISTemporalAA_UI
			ISTemporalAA_Water = 153,						// BSImagespaceShaderISTemporalAA_Water
			ISUpsampleDynamicResolution = 154,				// BSImagespaceShaderISUpsampleDynamicResolution
			ISWaterBlend = 155,								// BSImagespaceShaderISWaterBlend
			ISUnderwaterMask = 156,							// BSImagespaceShaderISUnderwaterMask
			ISWaterFlow = 157,								// BSImagespaceShaderWaterFlow
			Total = 159,
		};

		struct ApplyReflectionsShaderInfo
		{
			BSShader*	shader;
			bool		isEnabled;
		};
		static_assert(sizeof(ApplyReflectionsShaderInfo) == 0x10);

		struct ApplyVolumetricLightingShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
		};
		static_assert(sizeof(ApplyVolumetricLightingShaderInfo) == 0x10);

		struct BasicCopyShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
		};
		static_assert(sizeof(BasicCopyShaderInfo) == 0x10);

		struct IBLFShaderInfo
		{
			BSShader*           ISBlurShader;
			BSShader*           ISDownsampleShader;
			BSShader*           ISDownsampleIgnoreBrightestShader;
			BSShader*           ISDownsampleCSShader;
			BSShader*           ISDownsampleIgnoreBrightestCSShader;
			BSShader*           ISIBLensFlaresShader;
			bool                isEnabled;
			uint64_t            unk38;
			uint64_t            unk40;
			uint32_t            unk48;
			uint32_t            unk4C;
			uint32_t            unk50;
			uint32_t            unk54;
			bool                unk58;
			uint64_t            unk60;
			uint64_t            unk68;
			uint32_t            unk70;
			uint32_t            unk74;
			uint32_t            unk78;
			uint32_t            unk7C;
			bool                unk80;
		};
		static_assert(sizeof(IBLFShaderInfo) == 0x88);

		struct BlurCSShaderInfo
		{
			BSShader*   ISVolumetricLightingBlurHCSShader;
			BSShader*   ISVolumetricLightingBlurVCSShader;
			BSShader*   ISReflectionBlurHCSShader;
			BSShader*   ISReflectionBlurVCSShader;
			BSShader*   ISParallaxMaskHCSShader;
			BSShader*   ISParallaxMaskVCSShader;
			BSShader*   ISDepthOfFieldBlurHCSShader;
			BSShader*   ISDepthOfFieldBlurVCSShader;
			bool        isEnabled;
		};
		static_assert(sizeof(BlurCSShaderInfo) == 0x48);

		struct CompositeLensFlareVolumetricLightingShaderInfo
		{
			BSShader* ISCompositeVolumetricLightingShader;
			BSShader* ISCompositeLensFlareVCSShader;
			BSShader* ISCompositeLensFlareVolumetricLightingShader;
			bool      isEnabled;
		};
		static_assert(sizeof(CompositeLensFlareVolumetricLightingShaderInfo) == 0x20);

		struct CopySubRegionCSShaderInfo
		{
			BSShader*   ISCopySubRegionCSShader;
			bool        isEnabled;
			uint64_t    unk10;
			uint64_t    unk18;
			uint64_t    unk20;
			uint64_t    unk28;
			uint64_t    unk30;
			uint64_t    unk38;
			uint64_t    unk40;
			uint64_t    unk48;
			uint64_t    unk50;
			uint64_t    unk58;
			uint64_t    unk60;
		};
		static_assert(sizeof(CopySubRegionCSShaderInfo) == 0x68);

		struct DebugSnowShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
		};
		static_assert(sizeof(DebugSnowShaderInfo) == 0x10);

		struct IBExponentialPreFilterShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
			uint32_t  unk0C;
			uint32_t  unk10;
		};
		static_assert(sizeof(IBExponentialPreFilterShaderInfo) == 0x18);

		struct LightingCompositeShaderInfo
		{
			BSShader* ISLightingCompositeShader;
			BSShader* ISLightingCompositeNoDirectionalLightShader;
			BSShader* ISLightingCompositeMenuShader;
			bool      isEnabled;
		};
		static_assert(sizeof(LightingCompositeShaderInfo) == 0x20);

		struct PerlinNoiseCSShaderInfo
		{
			BSShader* ISPerlinNoiseCSShader;
			BSShader* ISPerlinNoise2DCSShader;
			bool      isEnabled;
		};
		static_assert(sizeof(PerlinNoiseCSShaderInfo) == 0x18);

		struct ReflectionsShaderInfo
		{
			BSShader*			ISReflectionsRayTracingShader;
			BSShader*           ISReflectionsDebugSpecMaskShader;
			bool                isEnabled;
			bool				unk11;
			BSTArray<void*>     unk18;
			bool				syncReflection;
			uint32_t            unk34;
		};
		static_assert(sizeof(ReflectionsShaderInfo) == 0x38);

		struct ScalableAmbientObscuranceShaderInfo
		{
			BSShader*       ISSAOBlurHShader;
			BSShader*       ISSAOBlurVShader;
			BSShader*       ISSAOCameraZShader;
			BSShader*       ISSAOCompositeSAOShader;
			BSShader*       ISSAOCompositeFogShader;
			BSShader*       ISSAOCompositeSAOFogShader;
			BSShader*       ISMinifyShader;
			BSShader*       ISMinifyContrastShader;
			BSShader*       ISSAORawAOShader;
			BSShader*       ISSAORawAONoTemporalShader;
			bool            isEnabled;
			uint32_t        unk54;
			uint64_t        unk58;
			uint64_t        unk60;
			uint64_t        unk68;
		};
		static_assert(sizeof(ScalableAmbientObscuranceShaderInfo) == 0x70);

		struct SAOCSShaderInfo
		{
			BSShader*   ISSAOBlurHCShader;
			BSShader*   ISSAOBlurVCShader;
			BSShader*   ISSAOCameraZAndMipsCShader;
			BSShader*   ISSAORawAOCSShader;
			bool        isEnabled;
			uint32_t    unk24;
			uint32_t    unk28;
			uint32_t    unk2C;
			uint32_t    unk30;
			bool        unk34;
			bool        unk35;
			bool        unk36;
		};
		static_assert(sizeof(SAOCSShaderInfo) == 0x38);

		struct IndirectLightingShaderInfo
		{
			BSShader* ISSILCompositeShader;
			BSShader* ISSILRawIndShader;
			bool      isEnabled;
			uint32_t  unk14;
		};
		static_assert(sizeof(IndirectLightingShaderInfo) == 0x18);

		struct SimpleColorShaderInfo
		{
			BSShader*   ISSimpleColorShader;
			BSShader*   ISDisplayDepthShader;
			bool        isEnabled;
			uint64_t    unk18;
			uint32_t    unk20;
			uint32_t    unk24;
			uint32_t    unk28;
			uint32_t    unk2C;
			uint32_t    unk30;
			float       unk34 = 0.9f;
			float       unk38 = 1.0f;
		};
		static_assert(sizeof(SimpleColorShaderInfo) == 0x40);

		struct SnowSSSShaderInfo
		{
			BSShader* ISSnowSSSShader;
			bool      isEnabled;
			uint32_t  unk0C;
			uint64_t  unk10;
			uint64_t  unk18;
			uint64_t  unk20;
			uint64_t  unk28;
		};
		static_assert(sizeof(SnowSSSShaderInfo) == 0x30);

		struct TemporalAAShaderInfo
		{
			BSShader* ISTemporalAAShader;
			BSShader* ISTemporalAA_UIShader;
			BSShader* ISTemporalAA_WaterShader;
			bool      isEnabled;
			float	  unk1C = 0.1f;
			float     unk20 = 0.1f;
			float     unk24 = 1.0f;
			float     unk28 = 1.0f;
			uint32_t  unk2C = 63;
			uint32_t  unk30;
			uint32_t  unk34;
			bool      taaWaterBlendingEnabled;
		};
		static_assert(sizeof(TemporalAAShaderInfo) == 0x40);

		struct UpsampleDynamicResolutionShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
		};
		static_assert(sizeof(UpsampleDynamicResolutionShaderInfo) == 0x10);

		struct WaterBlendShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
			uint32_t  unk0C = 1;
		};
		static_assert(sizeof(WaterBlendShaderInfo) == 0x10);

		struct UnderwaterMaskShaderInfo
		{
			BSShader* shader;
			bool      isEnabled;
			uint64_t  unk10 = 0;
		};
		static_assert(sizeof(UnderwaterMaskShaderInfo) == 0x18);

		struct ShaderInfo
		{
			ImageSpaceBaseData                              unk00;
			uint64_t										unk50[10];
			ApplyReflectionsShaderInfo*						applyReflectionsShaderInfo;
			ApplyVolumetricLightingShaderInfo*				applyVolumetricLightingShaderInfo;
			BasicCopyShaderInfo*							basicCopyShaderInfo;
			IBLFShaderInfo*									iblfShaderInfo;
			BlurCSShaderInfo*								blurCSShaderInfo;
			CompositeLensFlareVolumetricLightingShaderInfo* compositeLensFlareVolumetricLightingShaderInfo;
			CopySubRegionCSShaderInfo*                      copySubRegionCSShaderInfo;
			DebugSnowShaderInfo*							debugSnowShaderInfo;
			IBExponentialPreFilterShaderInfo*               ibExponentialPreFilterShaderInfo;
			LightingCompositeShaderInfo*					lightingCompositeShaderInfo;
			PerlinNoiseCSShaderInfo*						perlinNoiseCSShaderInfo;
			ReflectionsShaderInfo*                          reflectionsShaderInfo;
			ScalableAmbientObscuranceShaderInfo*            scalableAmbientObscuranceShaderInfo;
			SAOCSShaderInfo*								saoCSShaderInfo;
			IndirectLightingShaderInfo*                     indirectLightingShaderInfo;
			SimpleColorShaderInfo*                          simpleColorShaderInfo;
			SnowSSSShaderInfo*								snowSSSShaderInfo;
			TemporalAAShaderInfo*                           temporalAAShaderInfo;
			UpsampleDynamicResolutionShaderInfo*			upsampleDynamicResolutionShaderInfo;
			WaterBlendShaderInfo*							waterBlendShaderInfo;
			UnderwaterMaskShaderInfo*						underwaterMaskShaderInfo;
		};
		static_assert(sizeof(ShaderInfo) == 0x148);

		static ImageSpaceEffectManager* GetSingleton()
		{
			REL::Relocation<ImageSpaceEffectManager**> singleton{ Offset::ImageSpaceEffectManager::Singleton };
			return *singleton;
		}

		uint64_t								unk00;
		uint64_t								unk08;
		uint64_t								unk10;
		uint64_t								unk18;
		NiTPrimitiveArray<ImageSpaceEffect*>	effects;
		uint8_t									unk38;
		uint32_t								pad3C;
		uint32_t								unk40;
		uint64_t								unk48;
		uint64_t								unk50;
		uint8_t									unk58;
		uint32_t                                unk5C;
		uint32_t                                unk60;
		uint32_t                                unk64;
		uint64_t								unk68;
		uint64_t								unk70;
		uint64_t								unk78;
		uint32_t								unk80;
		uint32_t								unk84;
		uint32_t								unk88;
		uint32_t								unk8C;
		uint8_t									unk90;
		uint64_t								unk98;
		uint64_t                                unkA0;
		ImageSpaceBaseData*                     unkA8;
		ImageSpaceBaseData*                     unkB0;
		uint64_t								unkB8;
		uint64_t								unkC0;
		ShaderInfo                              shaderInfo;
		bool									postponeBlurryEffect;
		bool                                    unk211;
		uint64_t								unk218;
	};
	static_assert(sizeof(ImageSpaceEffectManager) == 0x220);
}
