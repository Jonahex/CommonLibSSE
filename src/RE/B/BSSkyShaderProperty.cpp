#include "RE/B/BSSkyShaderProperty.h"

#include "RE/B/BSRenderPass.h"
#include "RE/B/BSSkyShader.h"
#include "RE/S/State.h"

namespace RE
{
	BSSkyShaderProperty::RenderPassArray* BSSkyShaderProperty::GetRenderPasses(BSGeometry* geometry, RenderMode renderMode, [[maybe_unused]] BSShaderAccumulator* accumulator)
	{
		return GetRenderPassesImpl(geometry, renderMode, accumulator);
	}

	BSSkyShaderProperty::RenderPassArray* BSSkyShaderProperty::GetRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, [[maybe_unused]] BSShaderAccumulator* accumulator)
	{
		if (lastRenderPassState == std::numeric_limits<std::int32_t>::max()) 
		{
			renderPassList.Clear();

			switch (objectType.get()) 
			{
			case SkyObjectType::SunGlare:
				renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkySunGlare));
				break;
			case SkyObjectType::Clouds:
				{
					BSRenderPass* cloudsPass = nullptr;
					if (blendValue <= 0.f) 
					{
						cloudsPass = renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkyClouds));
					} 
					else 
					{
						auto* graphicsState = BSGraphics::State::GetSingleton();
						fadeSecondTexture = baseTexture == graphicsState->defaultTexEffectMap;
						if (baseTexture == graphicsState->defaultTexEffectMap || blendTexture == graphicsState->defaultTexEffectMap) 
						{
							cloudsPass = renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkyCloudsFade));
						} 
						else 
						{
							cloudsPass = renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkyCloudsLerp));
						}
					}
					cloudsPass->accumulationHint = BSRenderPass::AccumulationHint::Clouds;
				}
				break;
			case SkyObjectType::Atmosphere:
				renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkySky));
				break;
			case SkyObjectType::Stars:
				renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkyStars));
				break;
			case SkyObjectType::MoonShadow:
				renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkyMoonAndStarsMask));
				break;
			default:
				renderPassList.EmplacePass(BSSkyShader::GetSingleton(), this, geometry, static_cast<uint32_t>(ShaderTechnique::SkyTexture));
				break;
			}

			lastRenderPassState = 1;
		}
		if (renderMode == RenderMode::Depth || renderMode == RenderMode::SpotShadowmap || 
			renderMode == RenderMode::DirectionalShadowmap || renderMode == RenderMode::OmnidirectionalShadowmap || 
			renderMode == RenderMode::FirstPersonView || renderMode == RenderMode::BloodSplatter) 
		{
			return nullptr;
		}
		return &renderPassList;
	}
}
