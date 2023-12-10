#include "RE/B/BSSkyShader.h"

#include "RE/B/BSGeometry.h"
#include "RE/B/BSGraphicsUtils.h"
#include "RE/B/BSRenderPass.h"
#include "RE/B/BSShaderAccumulator.h"
#include "RE/B/BSShaderManager.h"
#include "RE/B/BSSkyShaderProperty.h"
#include "RE/I/ImageSpaceManager.h"
#include "RE/M/Main.h"
#include "RE/N/NiCamera.h"
#include "RE/R/Renderer.h"
#include "RE/R/RendererState.h"
#include "RE/S/State.h"

namespace RE
{
	BSSkyShader::LocalTechnique BSSkyShader::GetLocalTechnique(uint32_t globalTechnique)
	{
		switch (globalTechnique) 
		{
		case static_cast<uint32_t>(ShaderTechnique::SkySunOcclude):
			return LocalTechnique::SunOcclude;
		case static_cast<uint32_t>(ShaderTechnique::SkySky):
			return LocalTechnique::Sky;
		case static_cast<uint32_t>(ShaderTechnique::SkyMoonAndStarsMask):
			return LocalTechnique::MoonAndStarsMask;
		case static_cast<uint32_t>(ShaderTechnique::SkyStars):
			return LocalTechnique::Stars;
		case static_cast<uint32_t>(ShaderTechnique::SkyTexture):
			return LocalTechnique::Texture;
		case static_cast<uint32_t>(ShaderTechnique::SkyClouds):
			return LocalTechnique::Clouds;
		case static_cast<uint32_t>(ShaderTechnique::SkyCloudsLerp):
			return LocalTechnique::CloudsLerp;
		case static_cast<uint32_t>(ShaderTechnique::SkyCloudsFade):
			return LocalTechnique::CloudsFade;
		case static_cast<uint32_t>(ShaderTechnique::SkySunGlare):
			return LocalTechnique::SunGlare;
		}

		return LocalTechnique::SunOcclude;
	}

	BSSkyShader::LocalTechnique BSSkyShader::GetVertexTechnique(LocalTechnique localTechnique)
	{
		return localTechnique;
	}

	BSSkyShader::LocalTechnique BSSkyShader::GetPixelTechnique(LocalTechnique localTechnique)
	{
		return localTechnique;
	}

	NiColorA& BSSkyShader::GetAtmosphereBlendColor(size_t colorIndex)
	{
		static REL::Relocation<NiColorA*> colors(RELOCATION_ID(528199, 415145));
		return colors.get()[colorIndex];
	}

	NiPoint2& BSSkyShader::GetCloudLayerOffset(size_t cloudLayerIndex)
	{
		static REL::Relocation<NiPoint2*> cloudLayerOffset(RELOCATION_ID(528203, 415144));
		return cloudLayerOffset.get()[cloudLayerIndex];
	}

	bool BSSkyShader::SetupTechnique(uint32_t globalTechnique)
	{
		return SetupTechniqueImpl(globalTechnique);
	}

	bool BSSkyShader::SetupTechniqueImpl(uint32_t globalTechnique)
	{
		const LocalTechnique localTechnique = GetLocalTechnique(globalTechnique);
		const LocalTechnique vertexTechnique = GetVertexTechnique(localTechnique);
		const LocalTechnique pixelTechnique = GetPixelTechnique(localTechnique);

		if (!BeginTechnique(static_cast<uint32_t>(vertexTechnique), static_cast<uint32_t>(pixelTechnique), false)) 
		{
			return false;
		}

		CurrentTechnique = static_cast<uint32_t>(localTechnique);

		auto* rendererState = BSGraphics::RendererState::GetSingleton();

		rendererState->SetDepthStencilDepthMode(BSGraphics::DepthStencilDepthMode::kTest);

		switch (localTechnique) 
		{
		case LocalTechnique::SunOcclude:
			rendererState->SetAlphaBlendWriteMode(BSGraphics::AlphaBlendWriteMode::Mode0);
			break;

		case LocalTechnique::SunGlare:
			rendererState->SetDepthStencilDepthMode(BSGraphics::DepthStencilDepthMode::kDisabled);
			rendererState->SetAlphaBlendMode(BSGraphics::AlphaBlendMode::Mode2);
			rendererState->SetAlphaBlendWriteMode(BSGraphics::AlphaBlendWriteMode::ModeB);
			break;

		case LocalTechnique::MoonAndStarsMask:
			rendererState->SetAlphaTestEnabled(true);
			rendererState->SetAlphaBlendWriteMode(BSGraphics::AlphaBlendWriteMode::Mode0);
			rendererState->SetDepthStencilDepthMode(BSGraphics::DepthStencilDepthMode::kTestWrite);
			rendererState->SetDepthBiasMode(BSGraphics::DepthBiasMode::Mode3);
			break;

		case LocalTechnique::Stars:
			rendererState->SetAlphaBlendMode(BSGraphics::AlphaBlendMode::Mode2);
			break;

		case LocalTechnique::Clouds:
		case LocalTechnique::CloudsLerp:
		case LocalTechnique::CloudsFade:
		case LocalTechnique::Texture:
			rendererState->SetAlphaBlendMode(BSGraphics::AlphaBlendMode::Mode1);
			rendererState->SetDepthBiasMode(BSGraphics::DepthBiasMode::Mode2);
			break;

		case LocalTechnique::Sky:
			rendererState->SetAlphaBlendMode(BSGraphics::AlphaBlendMode::Mode1);
			break;
		}

		rendererState->SetPSTexture(static_cast<size_t>(TextureSlot::NoiseGrad), BSGraphics::State::GetSingleton()->defaultTextureDitherNoiseMap->rendererTexture);
		rendererState->SetPSTextureAddressMode(static_cast<size_t>(TextureSlot::NoiseGrad), BSGraphics::TextureAddressMode::kWrapSWrapT);
		rendererState->SetPSTextureFilterMode(static_cast<size_t>(TextureSlot::NoiseGrad), BSGraphics::TextureFilterMode::kNearest);

		return true;
	}

	void BSSkyShader::RestoreTechnique(uint32_t globalTechnique)
	{
		return RestoreTechniqueImpl(globalTechnique);
	}

	void BSSkyShader::RestoreTechniqueImpl([[maybe_unused]] uint32_t globalTechnique)
	{
		auto* rendererState = BSGraphics::RendererState::GetSingleton();

		rendererState->SetAlphaBlendMode(BSGraphics::AlphaBlendMode::Mode0);
		rendererState->SetAlphaBlendWriteMode(BSGraphics::AlphaBlendWriteMode::Mode1);
		rendererState->SetDepthStencilDepthMode(BSGraphics::DepthStencilDepthMode::kTestWrite);
		rendererState->SetAlphaTestEnabled(false);
		rendererState->SetDepthBiasMode(BSGraphics::DepthBiasMode::Mode0);

		EndTechnique();
	}

	void BSSkyShader::SetupGeometry(BSRenderPass* pass, RenderFlags flags)
	{
		return SetupGeometryImpl(pass, flags);
	}

	void BSSkyShader::SetupGeometryImpl(BSRenderPass * pass, [[maybe_unused]] RenderFlags flags)
	{
		using namespace BSGraphics;

		auto* rendererState = RendererState::GetSingleton();
		auto* state = State::GetSingleton();

		auto* property = static_cast<const BSSkyShaderProperty*>(pass->shaderProperty);
		auto* accumulator = BSShaderManager::GetCurrentAccumulator(); 

		Renderer::PrepareVSConstantGroup(ConstantGroupLevel::PerGeometry);
		Renderer::PreparePSConstantGroup(ConstantGroupLevel::PerGeometry);

		//
		// VS: p0 float4x4 WorldViewProj
		// VS: p1 float4x4 World
		//
		NiTransform world = pass->geometry->world;
		if (accumulator->firstPerson) 
		{
			auto*    worldRootCamera = Main::WorldRootCamera();
			NiPoint3 adjusted = world.translate - worldRootCamera->world.translate;
			if (accumulator->camera != nullptr) 
			{
				adjusted += accumulator->camera->world.translate;
			}
			world.translate = adjusted;
		}
		world.translate -= rendererState->posAdjust;

		rendererState->SetVSConstant(XMMatrixMultiplyTranspose(Utils::ConvertTransform(world), rendererState->cameraData.viewProjMat), ConstantGroupLevel::PerGeometry, 0);
		rendererState->SetVSConstant(XMMatrixTranspose(Utils::ConvertTransform(world)), ConstantGroupLevel::PerGeometry, 1);

		//
		// VS: p2 float4x4 PreviousWorld
		//
		// NOTE: Unlike BSDistantTreeShader and BSGrassShader, this uses GetPreviousWorldTransform() instead
		// of GetWorldTransform()...?
		//
		NiTransform previousWorld = pass->geometry->previousWorld;
		previousWorld.translate -= rendererState->previousPosAdjust;
		rendererState->SetVSConstant(XMMatrixTranspose(Utils::ConvertTransform(previousWorld)), ConstantGroupLevel::PerGeometry, 2);

		//
		// VS: p4 float3 EyePosition (adjusted to relative coordinates, not world)
		//
		{
			const auto adjustedEyePosition = accumulator->eyePosition - rendererState->posAdjust;
			rendererState->SetVSConstant(adjustedEyePosition, ConstantGroupLevel::PerGeometry, 4);
		}

		const float invFrameBufferRange = BSShaderManager::State::GetSingleton().invFrameBufferRange;
		const float skyScale = ImageSpaceManager::GetSingleton()->data.baseData.hdr.skyScale;

		//
		// PS: p0 float2 PParams
		//
		const auto localTechnique = static_cast<BSSkyShader::LocalTechnique>(CurrentTechnique);
		{
			::DirectX::XMFLOAT2 pparams;
			if (property->objectType == BSSkyShaderProperty::SkyObjectType::Clouds) 
			{
				if (localTechnique == LocalTechnique::CloudsFade && !property->fadeSecondTexture) 
				{
					pparams.x = 1.0f - property->blendValue;
				} 
				else 
				{
					pparams.x = property->blendValue;
				}

				pparams.y = invFrameBufferRange * skyScale;

				// VS: p5 float2 TexCoordOff
				rendererState->SetVSConstant(GetCloudLayerOffset(property->cloudLayer), ConstantGroupLevel::PerGeometry, 5);
			} 
			else if (property->objectType != BSSkyShaderProperty::SkyObjectType::Moon && property->objectType != BSSkyShaderProperty::SkyObjectType::SunGlare) 
			{
				pparams.y = invFrameBufferRange * skyScale;
			} 
			else 
			{
				pparams.y = 0.0f;
			}

			rendererState->SetPSConstant(pparams, ConstantGroupLevel::PerGeometry, 0);
		}

		//
		// VS: p6 float VParams
		//
		rendererState->SetVSConstant(invFrameBufferRange, ConstantGroupLevel::PerGeometry, 6);

		//
		// VS: p3 float4 BlendColor[3]
		//
		std::array<::DirectX::XMVECTOR, 3> BlendColors;
		switch (property->objectType.get()) 
		{
		case BSSkyShaderProperty::SkyObjectType::Sun:
		case BSSkyShaderProperty::SkyObjectType::SunGlare:
		case BSSkyShaderProperty::SkyObjectType::Clouds:
		case BSSkyShaderProperty::SkyObjectType::Stars:
		case BSSkyShaderProperty::SkyObjectType::Moon:
		case BSSkyShaderProperty::SkyObjectType::MoonShadow:
			BlendColors[0] = Utils::ConvertColorA(property->color);
			BlendColors[1] = Utils::ConvertColorA(NiColorA::Empty());
			BlendColors[2] = Utils::ConvertColorA(NiColorA::Empty());
			break;

		case BSSkyShaderProperty::SkyObjectType::Atmosphere:
			BlendColors[0] = Utils::ConvertColorA(GetAtmosphereBlendColor(0));
			BlendColors[1] = Utils::ConvertColorA(GetAtmosphereBlendColor(1));
			BlendColors[2] = Utils::ConvertColorA(GetAtmosphereBlendColor(2));
			break;

		default:
			BlendColors[0] = Utils::ConvertColorA(NiColorA::Black());
			BlendColors[1] = Utils::ConvertColorA(NiColorA::Empty());
			BlendColors[2] = Utils::ConvertColorA(NiColorA::Empty());
			break;
		}
		rendererState->SetVSConstant(BlendColors, ConstantGroupLevel::PerGeometry, 3);

		Renderer::FlushVSConstantGroup(ConstantGroupLevel::PerGeometry);
		Renderer::FlushPSConstantGroup(ConstantGroupLevel::PerGeometry);
		Renderer::ApplyVSConstantGroup(ConstantGroupLevel::PerGeometry);
		Renderer::ApplyPSConstantGroup(ConstantGroupLevel::PerGeometry);

		switch (localTechnique) 
		{
		case BSSkyShader::LocalTechnique::SunOcclude:
		case BSSkyShader::LocalTechnique::Stars:
			{
				auto baseSamplerTex = property->baseTexture;
				if (baseSamplerTex == nullptr) 
				{
					baseSamplerTex = state->defaultHeightMap;
				}

				rendererState->SetPSTexture(static_cast<size_t>(TextureSlot::Base), baseSamplerTex->rendererTexture);
				rendererState->SetPSTextureAddressMode(static_cast<size_t>(TextureSlot::Base), TextureAddressMode::kWrapSWrapT);
				rendererState->SetPSTextureFilterMode(static_cast<size_t>(TextureSlot::Base), TextureFilterMode::kBilinear);
			}
			break;

		case BSSkyShader::LocalTechnique::SunGlare:
		case BSSkyShader::LocalTechnique::MoonAndStarsMask:
		case BSSkyShader::LocalTechnique::Clouds:
		case BSSkyShader::LocalTechnique::CloudsLerp:
		case BSSkyShader::LocalTechnique::Texture:
			{
				auto baseSamplerTex = property->baseTexture;
				if (baseSamplerTex == nullptr) 
				{
					baseSamplerTex = state->defaultTextureNormalMap;
				}

				rendererState->SetPSTexture(static_cast<size_t>(TextureSlot::Base), baseSamplerTex->rendererTexture);
				rendererState->SetPSTextureAddressMode(static_cast<size_t>(TextureSlot::Base), TextureAddressMode::kWrapSWrapT);
				rendererState->SetPSTextureFilterMode(static_cast<size_t>(TextureSlot::Base), TextureFilterMode::kBilinear);

				if (CurrentTechnique == static_cast<uint32_t>(LocalTechnique::CloudsLerp)) 
				{
					auto blendSamplerTex = property->blendTexture;
					if (blendSamplerTex == nullptr) 
					{
						blendSamplerTex = property->baseTexture;
					}

					if (blendSamplerTex != nullptr) 
					{
						rendererState->SetPSTexture(static_cast<size_t>(TextureSlot::Blend), blendSamplerTex->rendererTexture);
						rendererState->SetPSTextureAddressMode(static_cast<size_t>(TextureSlot::Blend), TextureAddressMode::kWrapSWrapT);
						rendererState->SetPSTextureFilterMode(static_cast<size_t>(TextureSlot::Blend), TextureFilterMode::kBilinear);
					}
				}
			}
			break;

		case BSSkyShader::LocalTechnique::CloudsFade:
			{
				auto baseSamplerTex = property->baseTexture;
				if (property->fadeSecondTexture) 
				{
					baseSamplerTex = property->blendTexture;
				}
				if (baseSamplerTex == nullptr) 
				{
					baseSamplerTex = state->defaultTextureNormalMap;
				}

				rendererState->SetPSTexture(static_cast<size_t>(TextureSlot::Base), baseSamplerTex->rendererTexture);
				rendererState->SetPSTextureAddressMode(static_cast<size_t>(TextureSlot::Base), TextureAddressMode::kWrapSWrapT);
				rendererState->SetPSTextureFilterMode(static_cast<size_t>(TextureSlot::Base), TextureFilterMode::kBilinear);
			}
			break;
		}

		if (property->objectType == BSSkyShaderProperty::SkyObjectType::Sun || property->objectType == BSSkyShaderProperty::SkyObjectType::Moon) 
		{
			rendererState->SetAlphaBlendMode(AlphaBlendMode::Mode2);
		}
	}

	void BSSkyShader::RestoreGeometry(BSRenderPass* pass, RenderFlags flags)
	{
		return RestoreGeometryImpl(pass, flags);
	}

	void BSSkyShader::RestoreGeometryImpl(BSRenderPass* pass, [[maybe_unused]] RenderFlags flags)
	{
		auto* property = static_cast<const BSSkyShaderProperty*>(pass->shaderProperty);
		auto* rendererState = BSGraphics::RendererState::GetSingleton();
		if (property->objectType == BSSkyShaderProperty::SkyObjectType::Sun || property->objectType == BSSkyShaderProperty::SkyObjectType::Moon) 
		{
			rendererState->SetAlphaBlendMode(BSGraphics::AlphaBlendMode::Mode1);
		}
	}
}
