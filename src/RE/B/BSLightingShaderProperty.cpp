#include "RE/B/BSLightingShaderProperty.h"

#include "RE/B/BSEffectShader.h"
#include "RE/B/BSFadeNode.h"
#include "RE/B/BSGeometry.h"
#include "RE/B/BSLightingShader.h"
#include "RE/B/BSLightingShaderMaterialLandscape.h"
#include "RE/B/BSRenderPass.h"
#include "RE/B/BSShaderManager.h"
#include "RE/B/BSShadowDirectionalLight.h"
#include "RE/B/BSUtilityShader.h"
#include "RE/M/Misc.h"
#include "RE/S/Setting.h"
#include "RE/S/ShadowSceneNode.h"
#include "RE/S/State.h"

#include "SKSE/Logger.h"

namespace RE
{
	namespace SBSLightingShaderProperty
	{
		bool CalculateLODFade(float currentDistance, float previousDistance, float fadeStart, float fadeEnd, float& fadeValue, int32_t& lastRenderPassState)
		{
			if (currentDistance <= fadeEnd)
			{
				if (currentDistance <= fadeStart)
				{
					fadeValue = 1.0;
				}
				else
				{
					fadeValue = std::clamp((currentDistance - fadeEnd) / (fadeStart - fadeEnd), 0.f, 1.f);
					if (previousDistance > fadeEnd)
					{
						lastRenderPassState = 0x7FFFFFFF;
					}
				}

				return true;
			}

			if (previousDistance <= fadeEnd)
			{
				lastRenderPassState = 0x7FFFFFFF;
			}
			return false;
		}

		bool CalculateLODFade(float currentDistance, float fadeStart, float fadeEnd, float& fadeValue)
		{
			if (currentDistance <= fadeEnd)
			{
				if (currentDistance <= fadeStart)
				{
					fadeValue = 1.0;
				}
				else
				{
					fadeValue = std::clamp((currentDistance - fadeEnd) / (fadeStart - fadeEnd), 0.f, 1.f);
				}

				return true;
			}
			fadeValue = 0.f;
			return false;
		}

		bool CalculateSpecularLODFade(BSFadeNode* fadeNode, float& fadeValue, int32_t& lastRenderPassState)
		{
			const float fadeStart = RE::LightingShaderSettingsHelperInstance.fSpecularLODFadeStart->GetFloat();
			const float fadeEnd = RE::LightingShaderSettingsHelperInstance.fSpecularLODFadeEnd->GetFloat();
			return CalculateLODFade(fadeNode->currentDistance, fadeNode->currentFade, fadeStart, fadeEnd, fadeValue, lastRenderPassState);
		}

		bool CalculateDecalLODFade(BSFadeNode* fadeNode, BSGeometry* geometry, BSShaderAccumulator* accumulator, float& fadeValue, int32_t& lastRenderPassState)
		{
			const float fadeStart = RE::LightingShaderSettingsHelperInstance.fDecalLODFadeStart->GetFloat();
			const float fadeEnd = RE::LightingShaderSettingsHelperInstance.fDecalLODFadeEnd->GetFloat();

			if (fadeNode == BSFadeNode::GetFadeNodeAnim())
			{
				const NiPoint3 viewVector = geometry->worldBound.center - accumulator->eyePosition;
				const float    distance = std::clamp((viewVector.Length() - geometry->worldBound.radius) * 0.000033333334f, 0.f, 1.f);
				return CalculateLODFade(distance, fadeStart, fadeEnd, fadeValue);
			}
			return CalculateLODFade(fadeNode->currentDistance, fadeNode->currentFade, fadeStart, fadeEnd, fadeValue, lastRenderPassState);
		}

		bool CalculateEnvmapLODFade(BSFadeNode* fadeNode, float& fadeValue, int32_t& lastRenderPassState)
		{
			const float fadeStart = RE::LightingShaderSettingsHelperInstance.fEnvmapLODFadeStart->GetFloat();
			const float fadeEnd = RE::LightingShaderSettingsHelperInstance.fEnvmapLODFadeEnd->GetFloat();
			return CalculateLODFade(fadeNode->currentDistance, fadeNode->currentFade, fadeStart, fadeEnd, fadeValue, lastRenderPassState);
		}

		bool CalculateRefractionLODFade(BSFadeNode* fadeNode, float& fadeValue, int32_t& lastRenderPassState)
		{
			const float fadeStart = RE::LightingShaderSettingsHelperInstance.fRefractionLODFadeStart->GetFloat();
			const float fadeEnd = RE::LightingShaderSettingsHelperInstance.fRefractionLODFadeEnd->GetFloat();
			return CalculateLODFade(fadeNode->currentDistance, fadeNode->currentFade, fadeStart, fadeEnd, fadeValue, lastRenderPassState);
		}

		uint8_t GetShadowmapMask(const BSShadowLight& directionalLight, const BSShaderPropertyLightData& lightData)
		{
			uint8_t shadowMapMask = 0;
			for (uint32_t shadowMapIndex = 0; shadowMapIndex < directionalLight.shadowMapCount; ++shadowMapIndex)
			{
				shadowMapMask |= (1 << shadowMapIndex) & (lightData.flags >> 1);
			}
			return shadowMapMask;
		}

		uint32_t GetLightingTechnique(stl::enumeration<BSShaderProperty::EShaderPropertyFlag> flags, BSShaderMaterial* material, uint32_t pointLightCount, uint32_t shadowLightCount, bool hasPointShadowLights, bool shadowDirectionalLight, bool alphaTest, bool needsAdditionalAlphaMask)
		{
			using enum BSShaderProperty::EShaderPropertyFlag;
			using enum BSLightingShader::Flags;

			const bool bEnableImprovedSnow = RE::DisplaySettingsHelperInstance.bEnableImprovedSnow->GetBool();
			const bool bSimpleLighting = RE::DisplaySettingsHelperInstance.bSimpleLighting->GetBool();

			pointLightCount = std::min(pointLightCount, 7u);
			shadowLightCount = std::min(shadowLightCount, 4u);

			stl::enumeration<BSLightingShader::Flags> shaderFlags = static_cast<BSLightingShader::Flags>(((pointLightCount << 3) | (shadowLightCount << 6)));
			if (flags.any(kVertexColors))
			{
				shaderFlags.set(Vc);
			}
			if (flags.any(kSkinned))
			{
				shaderFlags.set(Skinned);
			}
			if (flags.any(kModelSpaceNormals))
			{
				shaderFlags.set(ModelSpaceNormals);
			}
			if (flags.any(kMultiIndexSnow, kSpecular))
			{
				shaderFlags.set(Specular);
			}
			if (flags.any(kSoftLighting))
			{
				shaderFlags.set(SoftLighting);
			}
			if (flags.any(kRimLighting))
			{
				shaderFlags.set(RimLighting);
			}
			if (flags.any(kBackLighting))
			{
				shaderFlags.set(BackLighting);
			}
			if (hasPointShadowLights)
			{
				shaderFlags.set(DefShadow);
			}
			if (shadowDirectionalLight)
			{
				shaderFlags.set(ShadowDir);
			}
			if (flags.any(kProjectedUV))
			{
				shaderFlags.set(ProjectedUv);
				if (flags.any(kSoftEffect) && flags.none(kHDLODObjects, kNoLODLandBlend, kLODObjects, kLODLandscape) && bEnableImprovedSnow)
				{
					shaderFlags.set(BaseObjectIsSnow);
				}
			}
			if (flags.any(kAnisotropicLighting))
			{
				shaderFlags.set(AnisoLighting);
			}
			if ((flags.any(kDynamicDecal, kDecal) && flags.none(kMultiIndexSnow)) || alphaTest)
			{
				shaderFlags.set(DoAlphaTest);
			}

			const bool isImprovedSnow = flags.none(kHDLODObjects, kNoLODLandBlend, kLODObjects, kLODLandscape) && ((flags.any(kSnow) && flags.none(kTreeAnim)) || flags.any(kSoftEffect)) && bEnableImprovedSnow;
			if (isImprovedSnow)
			{
				shaderFlags.set(Snow, Specular);
			}

			if (flags.any(kCharacterLighting))
			{
				shaderFlags.set(CharacterLight);
			}
			if (needsAdditionalAlphaMask)
			{
				shaderFlags.set(AdditionalAlphaMask);
			}
			if (flags.any(kHairTint) && flags.any(kZBufferWrite) && flags.any(kDynamicDecal, kDecal))
			{
				shaderFlags.set(ProjectedUv);
			}

			if (!bSimpleLighting && bEnableImprovedSnow)
			{
				if (flags.any(kMultiTextureLandscape) && !bSimpleLighting)
				{
					auto landscapeMaterial = static_cast<BSLightingShaderMaterialLandscape*>(material);
					for (float textureIsSnow : landscapeMaterial->textureIsSnow)
					{
						if (textureIsSnow == 1.f)
						{
							shaderFlags.set(Snow);
						}
					}
				}
			}

			if (flags.any(kHDLODObjects, kLODObjects, kLODLandscape) && flags.any(kMenuScreen))
			{
				shaderFlags.set(WorldMap);
			}

			BSLightingShader::LocalTechnique localTechnique = BSLightingShader::LocalTechnique::None;
			if (!bSimpleLighting)
			{
				if (flags.any(kEnvMap))
				{
					localTechnique = BSLightingShader::LocalTechnique::Envmap;
				}
				if (flags.any(kGlowMap))
				{
					localTechnique = BSLightingShader::LocalTechnique::Glowmap;
				}
				if (flags.any(kParallax) && flags.none(kParallaxOcclusion))
				{
					localTechnique = BSLightingShader::LocalTechnique::Parallax;
				}
				if (flags.any(kFace))
				{
					localTechnique = BSLightingShader::LocalTechnique::Facegen;
				}
				if (flags.any(kFaceGenRGBTint))
				{
					localTechnique = BSLightingShader::LocalTechnique::FacegenRgbTint;
				}
				if (flags.any(kHairTint))
				{
					localTechnique = BSLightingShader::LocalTechnique::Hair;
				}
				if (flags.any(kParallaxOcclusion))
				{
					localTechnique = BSLightingShader::LocalTechnique::ParallaxOcc;
				}
				if (flags.any(kMultiTextureLandscape))
				{
					localTechnique = BSLightingShader::LocalTechnique::MtLand;
				}
				if (flags.any(kNoLODLandBlend))
				{
					localTechnique = BSLightingShader::LocalTechnique::MtLandLodBlend;
				}
				if (flags.any(kLODLandscape))
				{
					localTechnique = BSLightingShader::LocalTechnique::LodLandNoise;
				}
				if (flags.any(kLODObjects))
				{
					localTechnique = BSLightingShader::LocalTechnique::LodObjects;
				}
				if (flags.any(kHDLODObjects))
				{
					localTechnique = BSLightingShader::LocalTechnique::LodObjectsHd;
				}
				if (flags.any(kHDLODObjects))
				{
					localTechnique = BSLightingShader::LocalTechnique::LodObjectsHd;
				}
				if (flags.any(kMultiLayerParallax))
				{
					localTechnique = BSLightingShader::LocalTechnique::MultiLayerParallax;
				}
				if (flags.any(kTreeAnim))
				{
					localTechnique = BSLightingShader::LocalTechnique::TreeAnim;
				}
				if (flags.all(kMultiIndexSnow, kProjectedUV))
				{
					localTechnique = BSLightingShader::LocalTechnique::MultiIndexSparkle;
				}
				if (flags.any(kEyeReflect))
				{
					localTechnique = BSLightingShader::LocalTechnique::Eye;
				}
			}

			return (static_cast<uint32_t>(localTechnique) << 24) | shaderFlags.underlying();
		}

		uint32_t GetRenderNormalTechnique(stl::enumeration<BSShaderProperty::EShaderPropertyFlag> flags)
		{
			using enum BSShaderProperty::EShaderPropertyFlag;
			using enum BSUtilityShader::Flags;

			stl::enumeration<BSUtilityShader::Flags> result;
			result.set(Texture, RenderNormal);

			if (flags.any(kModelSpaceNormals))
			{
				result.set(Normals, BinormalTangent);
			}
			if (flags.any(kVertexColors))
			{
				result.set(Vc);
			}
			if (flags.any(kSkinned))
			{
				result.set(Skinned);
			}
			if (flags.any(kFalloff))
			{
				result.set(RenderNormalFalloff);
			}
			if (flags.any(kNonProjectiveShadows))
			{
				result.set(RenderNormalClamp);
			}

			return result.underlying();
		}

		uint32_t GetRenderNormalClearTechnique(stl::enumeration<BSShaderProperty::EShaderPropertyFlag> flags)
		{
			using enum BSShaderProperty::EShaderPropertyFlag;
			using enum BSUtilityShader::Flags;

			stl::enumeration<BSUtilityShader::Flags> result;
			result.set(Texture, RenderNormalClear);

			if (flags.any(kModelSpaceNormals))
			{
				result.set(Normals, BinormalTangent);
			}
			if (flags.any(kVertexColors))
			{
				result.set(Vc);
			}
			if (flags.any(kSkinned))
			{
				result.set(Skinned);
			}

			return result.underlying();
		}

		uint32_t GetGrayscaleMaskTechnique(stl::enumeration<BSShaderProperty::EShaderPropertyFlag> flags)
		{
			using enum BSShaderProperty::EShaderPropertyFlag;
			using enum BSUtilityShader::Flags;

			stl::enumeration<BSUtilityShader::Flags> result;
			result.set(GrayscaleMask, RenderDepth, AlphaTest, Texture);

			if (flags.any(kVertexColors))
			{
				result.set(Vc);
			}
			if (flags.any(kSkinned))
			{
				result.set(Skinned);
			}
			if (flags.any(kModelSpaceNormals))
			{
				result.set(BinormalTangent, Normals);
			}

			return result.underlying();
		}

		uint32_t GetEffectShaderTechnique(stl::enumeration<BSShaderProperty::EShaderPropertyFlag> flags, BSEffectShaderData* effectData, const NiAlphaProperty* alphaProperty)
		{
			using enum BSShaderProperty::EShaderPropertyFlag;
			using enum BSEffectShader::Flags;

			stl::enumeration<BSEffectShader::Flags> result;
			result.set(Membrane, Texture, TexCoord);
			if (flags.any(kVertexColors))
			{
				result.set(Vc);
			}
			if (flags.any(kSkinned))
			{
				result.set(Skinned);
			}
			if (flags.any(kModelSpaceNormals))
			{
				result.set(BinormalTangent, Normals);
			}
			if (effectData->grayscaleToColor)
			{
				result.set(GrayscaleToColor);
			}
			if (effectData->grayscaleToAlpha)
			{
				result.set(GrayscaleToAlpha);
			}
			if (effectData->ignoreTextureAlpha)
			{
				result.set(IgnoreTexAlpha);
			}
			if (effectData->baseTextureProjectedUVs)
			{
				result.set(ProjectedUv);
			}
			if (!effectData->ignoreBaseGeomTexAlpha && alphaProperty != nullptr && alphaProperty->GetAlphaTesting())
			{
				result.set(AlphaTest);
			}
			if (effectData->lighting)
			{
				result.set(Lighting);
			}
			if (effectData->destBlend == NiAlphaProperty::AlphaFunction::kOne)
			{
				result.set(AddBlend);
			}

			return result.underlying();
		}

		bool GetUnkConstant0()
		{
			REL::Relocation<bool*> seconds{ RELOCATION_ID(513204, 390933) };
			return *seconds;
		}
	}

	void BSLightingShaderProperty::CopyMembers(BSLightingShaderProperty* a_other)
	{
		flags = a_other->flags;
		alpha = a_other->alpha;
		lastRenderPassState = std::numeric_limits<std::int32_t>::max();
		if (flags.all(EShaderPropertyFlag::kOwnEmit) && a_other->emissiveColor)
		{
			if (!emissiveColor)
			{
				emissiveColor = new NiColor();
			}
			emissiveColor->red = a_other->emissiveColor->red;
			emissiveColor->green = a_other->emissiveColor->green;
			emissiveColor->blue = a_other->emissiveColor->blue;
		}
		projectedUVParams = a_other->projectedUVParams;
		projectedUVColor = a_other->projectedUVColor;
		emissiveMult = a_other->emissiveMult;
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		return GetRenderPassesImpl(geometry, renderMode, accumulator);
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetDepthAndShadowmapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		return GetDepthAndShadowmapRenderPassesImpl(geometry, renderMode, accumulator);
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetLocalMapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		return GetLocalMapRenderPassesImpl(geometry, renderMode, accumulator);
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetPrecipitationOcclusionMapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		return GetPrecipitationOcclusionMapRenderPassesImpl(geometry, renderMode, accumulator);
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		using namespace SBSLightingShaderProperty;
		using enum EShaderPropertyFlag;

		const bool bEnableStippleFade = DisplaySettingsHelperInstance.bEnableStippleFade->GetBool();

		if (renderMode == RenderMode::DebugColor)
		{
			return GetDebugRenderPasses(geometry);
		}

		stl::enumeration<EShaderPropertyFlag> effectiveFlags = flags;

		float    currentFade = 1.0;
		if (!accumulator->unkB9)
		{
			currentFade = fadeNode->currentFade;

			if (effectiveFlags.any(kMultiIndexSnow, kSpecular))
			{
				const bool specularVisible = CalculateSpecularLODFade(fadeNode, specularLODFade, lastRenderPassState);
				if (!specularVisible)
				{
					effectiveFlags.reset(kSpecular);
				}
			}

			if (effectiveFlags.any(kDynamicDecal, kDecal) && effectiveFlags.none(kMultiIndexSnow, kSpecular))
			{
				float      decalLodFade = 1.f;
				const bool decalVisible = CalculateDecalLODFade(fadeNode, geometry, accumulator, decalLodFade, lastRenderPassState);
				if (decalVisible)
				{
					currentFade = currentFade * decalLodFade;
				}
				else
				{
					currentFade = 0.0;
				}
			}

			if ((effectiveFlags.any(kEnvMap)))
			{
				const bool envmapVisible = CalculateEnvmapLODFade(fadeNode, envmapLODFade, lastRenderPassState);
				if (!envmapVisible && effectiveFlags.none(kSnow))
				{
					effectiveFlags.reset(kEnvMap);
				}
			}
		}

		if (effectiveFlags.any(kRefraction, kTempRefraction) && effectiveFlags.none(kNoFade))
		{
			const bool refractionVisible = CalculateEnvmapLODFade(fadeNode, envmapLODFade, lastRenderPassState);
			if (!refractionVisible)
			{
				return &renderPassList;
			}
		}

		auto lightingMaterial = static_cast<BSLightingShaderMaterialBase*>(material);
		SetAlpha(lightingMaterial->materialAlpha * currentFade);

		const bool     unkFlag = !accumulator->unkB9 && geometry->flags.any(NiAVObject::Flag::Unk27) && renderPassList.head != nullptr && (renderPassList.head->LODMode.index != (fadeNode->unk152 & 0xF) || renderPassList.head->LODMode.singleLevel != false);
		const uint32_t     newRenderPassState = (lightData->flags) | (static_cast<uint32_t>(renderMode) << 8);
		const uint32_t affectingPointShadowLightsCount = lightData->GetAffectingPointShadowLightsCount(this);
		const bool     affectingPointShadowLightsCountChanged = renderPassList.head != nullptr && renderPassList.head->numShadowLights != affectingPointShadowLightsCount;
		if (!(unkFlag || lightData->hasLights || (newRenderPassState ^ lastRenderPassState) != 0 || renderMode == RenderMode::FirstPersonView || (affectingPointShadowLightsCount != 0) || affectingPointShadowLightsCountChanged))
		{
			return &renderPassList;
		}

		lightData->hasLights = false;
		if (alpha == 0.0 || !(effectiveFlags.none(kLocalMapClear) || BSShaderManager::State::GetSingleton().liteBrite) || 
			!(geometry->vertexDesc.HasFlag(BSGraphics::Vertex::Flags::Unk800) || geometry->vertexDesc.HasFlag(BSGraphics::Vertex::Flags::VF_UV)))
		{
			renderPassList.Clear();
			return &renderPassList;
		}

		BSRenderPass* nextPass = renderPassList.head;
		BSRenderPass* lastPass = nullptr;

		const auto alphaProperty = static_cast<NiAlphaProperty*>(geometry->properties[0].get());
		const bool useAlphaBlending = alphaProperty && alphaProperty->GetAlphaBlending();
		const bool useAlphaTesting = alphaProperty && alphaProperty->GetAlphaTesting();
		const bool translucent = IsTranslucent() || useAlphaBlending;
		const bool alphaTest = (BSGraphics::State::GetSingleton()->unk55 || translucent) && useAlphaTesting;

		if (effectiveFlags.any(kRefraction, kTempRefraction))
		{
			const uint32_t renderNormalTechnique = GetRenderNormalTechnique(effectiveFlags);
			auto           renderNormalPass = renderPassList.SetPass(nextPass, BSUtilityShader::GetSingleton(), this, geometry, renderNormalTechnique + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
			renderNormalPass->SetLights(0, nullptr);
			renderNormalPass->accumulationHint = BSRenderPass::AccumulationHint::Unk4;
			lastPass = renderNormalPass;
			nextPass = lastPass->next;
		}
		else
		{
			if (accumulator->unkB9)
			{
				const uint32_t renderNormalClearTechnique = GetRenderNormalClearTechnique(effectiveFlags);
				auto           renderNormalClearPass = renderPassList.SetPass(
                    nextPass,
                    BSUtilityShader::GetSingleton(),
                    this,
                    geometry,
                    renderNormalClearTechnique + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
				renderNormalClearPass->SetLights(0, nullptr);
				lastPass = renderNormalClearPass;
				nextPass = lastPass->next;
				renderNormalClearPass->accumulationHint = BSRenderPass::AccumulationHint::Unk5;
			}

			bool       stippleFade = bEnableStippleFade && fadeNode != nullptr && fadeNode->unk154 && currentFade < 1.0 && effectiveFlags.none(kScreendoorAlphaFade);
			const bool includeShadowLights = !(translucent && (!stippleFade || useAlphaBlending) && effectiveFlags.none(kAssumeShadowmask, kDynamicDecal, kDecal));
			bool       shadowDirectionalLight = !BSShaderManager::State::GetSingleton().interior;
			bool       needsAdditionalDepthPass = false;
			bool       needsAdditionalAlphaMask = stippleFade;

			uint32_t shadowLightCount = 0;
			BSLight* lights[BSRenderPass::MaxLightCount];
			uint32_t lightCount = lightData->GetLights(
				lights,
				BSRenderPass::MaxLightCount,
				shadowLightCount,
				accumulator->activeShadowSceneNode,
				this,
				includeShadowLights,
				shadowDirectionalLight,
				renderMode == RenderMode::FirstPersonView,
				accumulator->activeShadowSceneNode->unk248);
			const uint32_t pointLightCount = lightCount - 1;

			bool shadowLightsAllowed = accumulator->unk178;
			if (!stippleFade || useAlphaBlending)
			{
				shadowLightsAllowed = accumulator->unk178 && (alpha >= 1.0 && !useAlphaBlending && effectiveFlags.none(kLODLandscape) || effectiveFlags.any(kAssumeShadowmask, kDynamicDecal, kDecal));
			}

			bool hasPointShadowLights = shadowLightsAllowed;
			if (shadowLightsAllowed)
			{
				if (shadowLightCount == 0 && !shadowDirectionalLight)
				{
					hasPointShadowLights = false;
				}
			}
			else
			{
				shadowDirectionalLight = false;
				shadowLightCount = 0;
			}

			if (effectiveFlags.none(kAssumeShadowmask, kDynamicDecal, kDecal, kReceiveShadows) && !shadowmapRenderPassLists[0].head)
			{
				shadowDirectionalLight = false;
				hasPointShadowLights = false;
				shadowLightCount = 0;
			}

			auto lightingPass = renderPassList.SetPass(nextPass, BSLightingShader::GetSingleton(), this, geometry, 0);
			lastPass = lightingPass;
			nextPass = lastPass->next;
			if (geometry->flags.any(NiAVObject::Flag::Unk27))
			{
				lightingPass->LODMode.index = fadeNode->unk152 & 0xF;
				lightingPass->LODMode.singleLevel = false;
			}

			lightingPass->SetLights(static_cast<uint8_t>(lightCount), lights);
			lightingPass->numShadowLights = static_cast<uint8_t>(shadowLightCount);

			if (effectiveFlags.any(kDynamicDecal, kDecal))
			{
				if (translucent)
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk3;
				}
				else
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk2;
				}
			}
			else if (translucent)
			{
				if (currentFade >= 1.0)
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk1;
				}
				else if (effectiveFlags.any(kScreendoorAlphaFade))
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk10;
					shadowDirectionalLight = false;
					hasPointShadowLights = false;
					shadowLightCount = 0;
				}
				else
				{
					needsAdditionalDepthPass = !useAlphaBlending;
					if (needsAdditionalAlphaMask && !useAlphaBlending)
					{
						needsAdditionalAlphaMask = false;
						alpha = lightingMaterial->materialAlpha;
						if (effectiveFlags.any(kTreeAnim))
						{
							lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk11;
						}
						else if (!shadowDirectionalLight && !hasPointShadowLights && shadowLightCount == 0)
						{
							lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk15;
						}
					}
					else
					{
						lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk9;
					}
				}
			}
			else
			{
				if (effectiveFlags.any(kLODLandscape))
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk6;
				}
				else if (effectiveFlags.any(kHDLODObjects, kLODObjects))
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk7;
				}
				else if (effectiveFlags.any(kTreeAnim))
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk11;
				}
				else if (!shadowDirectionalLight && !hasPointShadowLights && shadowLightCount == 0)
				{
					lightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk15;
				}
			}

			uint8_t shadowMapMask = 0;
			if (shadowDirectionalLight && !hasPointShadowLights)
			{
				shadowMapMask = GetShadowmapMask(*accumulator->activeShadowSceneNode->shadowDirLight, *lightData);
				if (shadowMapMask == 0)
				{
					shadowDirectionalLight = false;
				}
			}
			lightingPass->extraParam = shadowMapMask;

			uint32_t lightingTechnique = GetLightingTechnique(effectiveFlags, material, pointLightCount, shadowLightCount, hasPointShadowLights, shadowDirectionalLight, alphaTest, needsAdditionalAlphaMask);

			lightingPass->passEnum = lightingTechnique + static_cast<uint32_t>(ShaderTechnique::LightingGeneralStart);
			if (geometry->flags.any(NiAVObject::Flag::Unk27))
			{
				if ((fadeNode->unk153 & 0x70) != 32)
				{
					auto passIt = renderPassList.head;
					while (passIt != nullptr)
					{
						if (passIt->accumulationHint == BSRenderPass::AccumulationHint::Unk14)
						{
							break;
						}
						auto additionalLightingPass = renderPassList.SetPass(
							nextPass,
							BSLightingShader::GetSingleton(),
							this,
							passIt->geometry,
							passIt->passEnum);
						additionalLightingPass->SetLights(passIt->numLights, passIt->numLights != 0 ? passIt->sceneLights : nullptr);
						additionalLightingPass->extraParam = passIt->extraParam;
						additionalLightingPass->LODMode.index = fadeNode->unk152 & 0xF;
						additionalLightingPass->LODMode.singleLevel = true;
						additionalLightingPass->accumulationHint = BSRenderPass::AccumulationHint::Unk14;
						lastPass = additionalLightingPass;
						nextPass = lastPass->next;

						passIt = passIt->next;
					}
				}
			}
			if (needsAdditionalDepthPass)
			{
				stl::enumeration<BSUtilityShader::Flags> additionalAlphaMaskTechnique;
				additionalAlphaMaskTechnique.set(static_cast<BSUtilityShader::Flags>(DetermineUtilityShaderDecl()), BSUtilityShader::Flags::RenderDepth);
				if (useAlphaTesting)
				{
					additionalAlphaMaskTechnique.set(BSUtilityShader::Flags::AlphaTest);
				}
				if (needsAdditionalAlphaMask)
				{
					additionalAlphaMaskTechnique.set(BSUtilityShader::Flags::AdditionalAlphaMask);
				}

				auto additionalAlphaMaskPass = renderPassList.SetPass(nextPass, BSUtilityShader::GetSingleton(), this, geometry, additionalAlphaMaskTechnique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
				additionalAlphaMaskPass->SetLights(0, nullptr);
				additionalAlphaMaskPass->accumulationHint = BSRenderPass::AccumulationHint::Unk14;

				lastPass = additionalAlphaMaskPass;
				nextPass = lastPass->next;
			}
		}

		if (effectData != nullptr && effectiveFlags.none(EShaderPropertyFlag::kEyeReflect) == 0)
		{
			const uint32_t effectShaderTechnique = GetEffectShaderTechnique(effectiveFlags, effectData.get(), alphaProperty);
			auto           effectPass = renderPassList.SetPass(nextPass, BSEffectShader::GetSingleton(), this, geometry, effectShaderTechnique + static_cast<uint32_t>(ShaderTechnique::EffectGeneralStart));
			effectPass->accumulationHint = (currentFade < 1.f) ? BSRenderPass::AccumulationHint::Unk1 : BSRenderPass::AccumulationHint::Unk3;
			effectPass->SetLights(0, nullptr);

			lastPass = effectPass;
			nextPass = lastPass->next;

			if (effectData->blockOutTexture != nullptr)
			{
				auto passIt = renderPassList.head;
				while (passIt != nullptr)
				{
					if (passIt->accumulationHint == BSRenderPass::AccumulationHint::Unk0 ||
						passIt->accumulationHint == BSRenderPass::AccumulationHint::Unk3 ||
						passIt->accumulationHint == BSRenderPass::AccumulationHint::Unk15)
					{
						passIt->accumulationHint = BSRenderPass::AccumulationHint::Unk16;
					}

					passIt = passIt->next;
				}

				const uint32_t effectBlockOutTechnique = GetGrayscaleMaskTechnique(effectiveFlags);
				auto           effectBlockOutPass = renderPassList.SetPass(
                    nextPass,
                    BSUtilityShader::GetSingleton(),
                    this,
                    geometry,
                    effectBlockOutTechnique + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
				effectBlockOutPass->accumulationHint = BSRenderPass::AccumulationHint::Unk14;
				effectBlockOutPass->SetLights(0, nullptr);

				lastPass = effectBlockOutPass;
				nextPass = lastPass->next;
			}
		}

		renderPassList.ClearAfter(lastPass);

		lastRenderPassState = newRenderPassState;
		//lastRenderPassState = std::numeric_limits<std::int32_t>::max();

		return &renderPassList;
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetDepthAndShadowmapRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		using enum EShaderPropertyFlag;
		using enum BSUtilityShader::Flags;

		const bool     bEnableStippleFade = DisplaySettingsHelperInstance.bEnableStippleFade->GetBool();
		const bool     bLodZPrepass = DisplaySettingsHelperInstance.bLodZPrepass->GetBool();
		const uint32_t iEnableShadowCastingFlag = DisplaySettingsHelperInstance.iEnableShadowCastingFlag->GetUInt();

		const auto alphaProperty = static_cast<NiAlphaProperty*>(geometry->properties[0].get());
		const bool useAlphaBlending = alphaProperty && alphaProperty->GetAlphaBlending();
		const bool useAlphaTesting = alphaProperty && alphaProperty->GetAlphaTesting();

		const bool isDecal = flags.any(kDynamicDecal, kDecal);
		const bool isHair = isDecal && flags.any(kHairTint);

		const auto  lightingMaterial = static_cast<BSLightingShaderMaterialBase*>(material);
		const float currentAlpha = fadeNode->currentFade * lightingMaterial->materialAlpha;

		const bool hasEffectBlockOut = effectData && effectData->blockOutTexture;

		struct BSRenderPass::LODMode defaultLODMode;
		uint8_t                      unkFlag = 0;
		if (geometry->flags.any(NiAVObject::Flag::Unk27))
		{
			defaultLODMode.index = fadeNode->unk152 & 0xF;
			unkFlag = fadeNode->unk153 >> 7;
		}

		if (shadowmapRenderPassLists[0].head != nullptr)
		{
			shadowmapRenderPassLists[0].MoveHead(shadowmapRenderPassLists[previousShadowmapRenderPassListIndex]);
		}
		if (lastFrameCount != BSGraphics::State::GetSingleton()->uiFrameCount)
		{
			shadowmapRenderPassLists[currentShadowmapRenderPassListIndex].Clear();
			currentShadowmapRenderPassListIndex = previousShadowmapRenderPassListIndex;
			previousShadowmapRenderPassListIndex = previousShadowmapRenderPassListIndex ^ 3;
		}

		if (renderMode == RenderMode::Depth || renderMode == RenderMode::SpotShadowmap || renderMode == RenderMode::DirectionalShadowmap || renderMode == RenderMode::OmnidirectionalShadowmap)
		{
			const bool unkFlag0 = !(!bEnableStippleFade || renderMode != RenderMode::Depth || !fadeNode->unk154 || fadeNode->currentFade >= 1.f || useAlphaBlending || flags.any(kScreendoorAlphaFade));
			const bool unkFlag1 = flags.any(kNoLODLandBlend, kMultiTextureLandscape) && unk108 < 1.f && renderMode == RenderMode::Depth;

			if (isHair && (flags.none(kZBufferWrite) || !useAlphaBlending))
			{
				return nullptr;
			}

			if ((currentAlpha >= 1.f || unkFlag0) && flags.none(kRefraction, kTempRefraction) && (!useAlphaBlending || isHair))
			{
				if (renderMode != RenderMode::Depth || !hasEffectBlockOut)
				{
					if (iEnableShadowCastingFlag == 2 && flags.none(kCastShadows) && renderMode == RenderMode::DirectionalShadowmap && accumulator->unk12E)
					{
						unk0D8.Clear();

						stl::enumeration<BSUtilityShader::Flags> shadowMapTechnique = static_cast<BSUtilityShader::Flags>(DetermineUtilityShaderDecl());
						shadowMapTechnique.set(GrayscaleToAlpha, RenderShadowmap);
						if (useAlphaTesting)
						{
							shadowMapTechnique.set(AlphaTest);
						}
						if (flags.any(kLODObjects, kHDLODObjects))
						{
							shadowMapTechnique.set(LodObject);
						}
						auto* shadowMapPass = unk0D8.EmplacePass(
							BSUtilityShader::GetSingleton(),
							this,
							geometry,
							shadowMapTechnique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
						shadowMapPass->LODMode = defaultLODMode;
						shadowMapPass->accumulationHint = BSRenderPass::AccumulationHint::Unk8;
						return &unk0D8;
					}

					if (flags.any(kCastShadows) || renderMode == RenderMode::Depth || iEnableShadowCastingFlag != 1)
					{
						if (bLodZPrepass || flags.none(kLODLandscape) || renderMode != RenderMode::Depth)
						{
							stl::enumeration<BSUtilityShader::Flags> technique;
							BSRenderPass*                            pass = nullptr;

							if (shadowmapRenderPassLists[currentShadowmapRenderPassListIndex].head != nullptr)
							{
								pass = shadowmapRenderPassLists[currentShadowmapRenderPassListIndex].MoveHead(shadowmapRenderPassLists[0]);
							}
							else
							{
								if (shadowmapRenderPassLists[previousShadowmapRenderPassListIndex].head != nullptr)
								{
									technique = stl::enumeration<BSUtilityShader::Flags>(static_cast<BSUtilityShader::Flags>((shadowmapRenderPassLists[previousShadowmapRenderPassListIndex].head->passEnum - static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart))));
									technique.reset(RenderDepth, RenderShadowmap, RenderShadowmapClamped, RenderShadowmapPb);
								}
								else
								{
									technique = static_cast<BSUtilityShader::Flags>(DetermineUtilityShaderDecl());
									if (useAlphaTesting)
									{
										technique.set(AlphaTest);
									}
								}
								if (technique.get() != BSUtilityShader::Flags::None)
								{
									pass = shadowmapRenderPassLists[0].EmplacePass(
										BSUtilityShader::GetSingleton(),
										this,
										geometry,
										technique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
									if (flags.any(kTreeAnim))
									{
										pass->accumulationHint = BSRenderPass::AccumulationHint::Unk11;
									}
								}
							}

							if (pass != nullptr)
							{
								pass->LODMode = defaultLODMode;

								if (renderMode == RenderMode::Depth)
								{
									technique.set(RenderDepth);
								}
								else
								{
									technique.set(RenderShadowmap);
									if (renderMode == RenderMode::DirectionalShadowmap)
									{
										technique.set(RenderShadowmapClamped);
									}
									else if (renderMode == RenderMode::OmnidirectionalShadowmap)
									{
										technique.set(RenderShadowmapPb);
									}
								}
								if (unkFlag1 || unkFlag0)
								{
									technique.set(AdditionalAlphaMask);
								}
								if (isDecal)
								{
									technique.set(DepthWriteDecals, AlphaTest);
								}
								if (flags.any(kLODObjects, kHDLODObjects))
								{
									technique.set(LodObject);
								}
								pass->passEnum = technique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart);

								if (isDecal)
								{
									pass->accumulationHint = BSRenderPass::AccumulationHint::Unk3;
								}
								if (flags.any(kLODObjects, kHDLODObjects) && renderMode == RenderMode::Depth)
								{
									pass->accumulationHint = BSRenderPass::AccumulationHint::Unk7;
								}
							}

							return &shadowmapRenderPassLists[0];
						}
					}
				}
			}
			return nullptr;
		}

		if (isHair)
		{
			if (flags.none(kZBufferWrite))
			{
				return nullptr;
			}
		}
		else if (currentAlpha < 1.0 || useAlphaBlending || flags.any(kLODLandscape, kRefraction, kTempRefraction) || hasEffectBlockOut)
		{
			shadowmaskRenderPassList.Clear();
			return nullptr;
		}

		if (flags.none(kReceiveShadows))
		{
			return nullptr;
		}

		const int32_t newRenderPassState = lightData->flags | (static_cast<int32_t>(renderMode) << 8);
		if (shadowmaskRenderPassList.head != nullptr && unkFlag == 0 && !lightData->hasLights && lastRenderPassState == newRenderPassState)
		{
			return &shadowmaskRenderPassList;
		}

		BSRenderPass* lastPass = nullptr;

		stl::enumeration<BSUtilityShader::Flags> baseShadowmaskTechnique = static_cast<BSUtilityShader::Flags>(DetermineUtilityShaderDecl());
		if (baseShadowmaskTechnique.get() != BSUtilityShader::Flags::None)
		{
			if (useAlphaTesting)
			{
				baseShadowmaskTechnique.set(AlphaTest);
			}

			if (SBSLightingShaderProperty::GetUnkConstant0())
			{
				if (renderMode == RenderMode::Unk17 || lightData->flags != 0)
				{
					auto depthWriteDecalsTechnique = baseShadowmaskTechnique;
					depthWriteDecalsTechnique.set(DepthWriteDecals);

					auto depthWriteDecalsPass = shadowmaskRenderPassList.EmplacePass(BSUtilityShader::GetSingleton(), this, geometry, depthWriteDecalsTechnique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
					depthWriteDecalsPass->LODMode = defaultLODMode;
					if (flags.any(kTreeAnim))
					{
						depthWriteDecalsPass->accumulationHint = BSRenderPass::AccumulationHint::Unk11;
					}
					else
					{
						depthWriteDecalsPass->accumulationHint = BSRenderPass::AccumulationHint::Unk0;
					}

					lastPass = depthWriteDecalsPass;
				}
			}
			else
			{
				bool          isFirst = true;
				uint8_t       shadowInfluenceBitIndex = 0;
				const uint32_t  shadowMapCount = accumulator->activeShadowSceneNode->shadowDirLight->shadowMapCount + BSRenderPass::MaxShadowLightCount;
				for (uint32_t shadowMapIndex = 0; shadowMapIndex < shadowMapCount; ++shadowMapIndex)
				{
					uint32_t shadowInfluenceMask = 1 << shadowInfluenceBitIndex;
					if (renderMode == RenderMode::Unk17 && (shadowInfluenceMask & accumulator->activeShadowSceneNode->unk248) != 0 || (shadowInfluenceMask & lightData->flags) != 0)
					{
						BSShadowLight* shadowLight = accumulator->activeShadowSceneNode->shadowCasterLights[shadowMapIndex];
						if (shadowLight == nullptr || !shadowLight->IsShadowLight())
						{
							continue;
						}

						const bool isSpot = shadowLight->IsSpotLight();
						const bool isParabolic = shadowLight->IsParabolicLight();
						const bool isOmnidirectional = shadowLight->IsOmnidirectionalLight();
						const bool isDirectional = !(isSpot || isParabolic || isOmnidirectional);

						if (isDirectional && !isFirst)
						{
							continue;
						}

						BSUtilityShader::Flags shadowmaskFlag = RenderShadowmask;
						if (isSpot)
						{
							shadowmaskFlag = RenderShadowmaskSpot;
						}
						else if (isOmnidirectional)
						{
							shadowmaskFlag = RenderShadowmaskDpb;
						}
						else if (isParabolic)
						{
							shadowmaskFlag = RenderShadowmaskPb;
						}

						stl::enumeration<BSUtilityShader::Flags> technique = baseShadowmaskTechnique;
						technique.set(shadowmaskFlag);

						BSRenderPass* shadowMaskPass = shadowmaskRenderPassList.EmplacePass(BSUtilityShader::GetSingleton(), this, geometry, technique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
						if (isFirst)
						{
							shadowMaskPass->LODMode = defaultLODMode;
							if (flags.any(kTreeAnim))
							{
								shadowMaskPass->accumulationHint = BSRenderPass::AccumulationHint::Unk11;
							}
							else
							{
								shadowMaskPass->accumulationHint = BSRenderPass::AccumulationHint::Unk0;
							}
							if (isDirectional)
							{
								uint8_t extraParam = 1;
								if (renderMode != RenderMode::Unk17)
								{
									extraParam = SBSLightingShaderProperty::GetShadowmapMask(*shadowLight, *lightData);
								}
								shadowMaskPass->extraParam = extraParam;
							}
						}
						else
						{
							shadowMaskPass->LODMode = lastPass->LODMode;
							shadowMaskPass->accumulationHint = lastPass->accumulationHint;
						}
						if (!isDirectional)
						{
							shadowMaskPass->extraParam = static_cast<uint8_t>(shadowLight->Unk_0D(shadowMapIndex));
						}

						BSLight* light = shadowLight;
						shadowMaskPass->SetLights(1, &light);

						isFirst = false;
						lastPass = shadowMaskPass;
					}
					++shadowInfluenceBitIndex;
				}

				if (!(isFirst || geometry->flags.none(NiAVObject::Flag::Unk27) || (fadeNode->unk153 & 0x70) == 32))
				{
					auto passIt = shadowmaskRenderPassList.head;
					while (passIt != nullptr)
					{
						if (passIt->accumulationHint == BSRenderPass::AccumulationHint::Unk10)
						{
							break;
						}

						auto duplicatePass = shadowmaskRenderPassList.EmplacePass(passIt->shader, this, passIt->geometry, passIt->passEnum);
						duplicatePass->SetLights(passIt->numLights, passIt->numLights != 0 ? passIt->sceneLights : nullptr);
						duplicatePass->LODMode.index = fadeNode->unk152 & 0xF;
						duplicatePass->LODMode.singleLevel = true;
						duplicatePass->accumulationHint = BSRenderPass::AccumulationHint::Unk10;

						passIt = passIt->next;

						lastPass = duplicatePass;
					}
				}
			}
		}

		shadowmaskRenderPassList.ClearAfter(lastPass);
		return &shadowmaskRenderPassList;
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetLocalMapRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator)
	{
		using enum EShaderPropertyFlag;
		using enum BSUtilityShader::Flags;

		if (flags.any(kMultiTextureLandscape))
		{
			return GetRenderPasses(geometry, renderMode, accumulator);
		}

		if (shadowmapRenderPassLists[0].head != nullptr)
		{
			shadowmapRenderPassLists[0].MoveHead(shadowmapRenderPassLists[previousShadowmapRenderPassListIndex]);
		}
		if (lastFrameCount != BSGraphics::State::GetSingleton()->uiFrameCount)
		{
			shadowmapRenderPassLists[currentShadowmapRenderPassListIndex].Clear();
			currentShadowmapRenderPassListIndex = previousShadowmapRenderPassListIndex;
			previousShadowmapRenderPassListIndex = previousShadowmapRenderPassListIndex ^ 3;
		}

		const auto newRenderPassState = static_cast<int32_t>(renderMode) << 8;

		auto alphaProperty = static_cast<NiAlphaProperty*>(geometry->properties[0].get());
		auto lightingMaterial = static_cast<BSLightingShaderMaterialBase*>(material);

		if (BSShaderManager::GetCurrentRenderMode() == RenderMode::LocalMapFogOfWar)
		{
			if (lastRenderPassState != newRenderPassState)
			{
				lastRenderPassState = newRenderPassState;
				renderPassList.Clear();

				stl::enumeration<BSUtilityShader::Flags> technique = static_cast<BSUtilityShader::Flags>(DetermineUtilityShaderDecl());
				technique.set(LocalMapFogOfWar);

				auto fogOfWarPass = renderPassList.EmplacePass(BSUtilityShader::GetSingleton(), this, geometry, technique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
				fogOfWarPass->accumulationHint = BSRenderPass::AccumulationHint::Unk0;
			}

			return &renderPassList;
		}
		else if (flags.none(kRefraction, kSkinned) && (!alphaProperty || !alphaProperty->GetAlphaBlending()) && (fadeNode->currentFade * lightingMaterial->materialAlpha) >= 1.0)
		{
			if (lastRenderPassState != newRenderPassState)
			{
				lastRenderPassState = newRenderPassState;
				renderPassList.Clear();

				stl::enumeration<BSUtilityShader::Flags> technique = static_cast<BSUtilityShader::Flags>(DetermineUtilityShaderDecl());
				technique.set(RenderBaseTexture);

				if (alphaProperty && alphaProperty->GetAlphaTesting())
				{
					technique.set(AlphaTest);
				}

				auto renderBaseTexturePass = renderPassList.EmplacePass(
					BSUtilityShader::GetSingleton(),
					this,
					geometry,
					technique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
				renderBaseTexturePass->accumulationHint = BSRenderPass::AccumulationHint::Unk0;
			}
			
			return &renderPassList;
		}

		return nullptr;
	}

	BSShaderProperty::RenderPassArray* BSLightingShaderProperty::GetPrecipitationOcclusionMapRenderPassesImpl(BSGeometry* geometry, [[maybe_unused]] RenderMode renderMode, [[maybe_unused]] BSShaderAccumulator* accumulator)
	{
		using enum EShaderPropertyFlag;
		using enum BSUtilityShader::Flags;

		if (flags.none(kRefraction, kTempRefraction, kZBufferWrite, kSkinned, kMultiTextureLandscape, kNoLODLandBlend, kLODLandscape, kEyeReflect, kTreeAnim, kDecal, kDynamicDecal, kAnisotropicLighting))
		{
			const auto alphaProperty = static_cast<NiAlphaProperty*>(geometry->properties[0].get());

			stl::enumeration<BSUtilityShader::Flags> technique;
			technique.set(RenderDepth, Texture);

			if (flags.any(kModelSpaceNormals))
			{
				technique.set(Normals, BinormalTangent);
			}
			if (flags.any(kVertexColors))
			{
				technique.set(Vc);
			}
			if (alphaProperty && alphaProperty->GetAlphaTesting())
			{
				technique.set(AlphaTest);
			}
			if (flags.any(kLODObjects, kHDLODObjects))
			{
				technique.set(LodObject);
			}

			precipitationOcclusionMapRenderPassList.EmplacePass(
				BSUtilityShader::GetSingleton(),
				this,
				geometry,
				technique.underlying() + static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart));
		}
		return &precipitationOcclusionMapRenderPassList;
	}
}
