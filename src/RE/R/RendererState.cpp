#include "RE/R/RendererState.h"

namespace RE::BSGraphics
{
	RendererState* RendererState::GetSingleton() noexcept
	{
		static REL::Relocation<RendererState*> singleton(RE::Offset::RendererStateInstance);
		return singleton.get();
	}

	ConstantGroup& RendererState::GetVSConstantGroup(ConstantGroupLevel level)
	{
		return currentVertexShader->constantBuffers[static_cast<size_t>(level)];
	}

	ConstantGroup& RendererState::GetPSConstantGroup(ConstantGroupLevel level)
	{
		return currentPixelShader->constantBuffers[static_cast<size_t>(level)];
	}

	void RendererState::SetDepthStencilDepthMode(DepthStencilDepthMode newDepthStencilDepthMode)
	{
		if (depthStencilDepthMode != newDepthStencilDepthMode)
		{
			depthStencilDepthMode = newDepthStencilDepthMode;
			if (referenceDepthStencilDepthMode == newDepthStencilDepthMode)
			{
				stateUpdateFlags.reset(StateUpdateFlags::DirtyDepthMode);
			}
			else 
			{
				stateUpdateFlags.set(StateUpdateFlags::DirtyDepthMode);
			}
		}
	}

	void RendererState::SetFillMode(FillMode newFillMode)
	{
		if (fillMode != newFillMode)
		{
			fillMode = newFillMode;
			stateUpdateFlags.set(StateUpdateFlags::DirtyFillMode);
		}
	}

	void RendererState::SetCullMode(CullMode newCullMode)
	{
		if (cullMode != newCullMode)
		{
			cullMode = newCullMode;
			stateUpdateFlags.set(StateUpdateFlags::DirtyCullMode);
		}
	}

	void RendererState::SetDepthBiasMode(DepthBiasMode newDepthBiasMode)
	{
		if (depthBiasMode != newDepthBiasMode)
		{
			depthBiasMode = newDepthBiasMode;
			stateUpdateFlags.set(StateUpdateFlags::DirtyDepthBias);
		}
	}

	void RendererState::SetScissorMode(ScissorMode newScissorMode)
	{
		if (scissorMode != newScissorMode)
		{
			scissorMode = newScissorMode;
			stateUpdateFlags.set(StateUpdateFlags::DirtyScissorMode);
		}
	}

	void RendererState::SetAlphaBlendMode(AlphaBlendMode newAlphaBlendMode)
	{
		if (alphaBlendMode != newAlphaBlendMode) 
		{
			alphaBlendMode = newAlphaBlendMode;
			stateUpdateFlags.set(StateUpdateFlags::DirtyAlphaBlend);
		}
	}

	void RendererState::SetAlphaBlendWriteMode(AlphaBlendWriteMode newAlphaBlendWriteMode)
	{
		if (alphaBlendWriteMode != newAlphaBlendWriteMode) 
		{
			alphaBlendWriteMode = newAlphaBlendWriteMode;
			stateUpdateFlags.set(StateUpdateFlags::DirtyAlphaBlend);
		}
	}

	void RendererState::SetAlphaTestEnabled(bool newEnabled)
	{
		if (alphaTestEnabled != newEnabled) 
		{
			alphaTestEnabled = newEnabled;
			stateUpdateFlags.set(StateUpdateFlags::DirtyAlphaEnableTest);
		}
	}

	void RendererState::SetPSTexture(size_t textureIndex, BSGraphics::Texture* newTexture)
	{
		ShaderResourceView* resourceView = newTexture ? newTexture->resourceView : nullptr;
		if (PSTexture[textureIndex] != resourceView)
		{
			PSTexture[textureIndex] = resourceView;
			PSResourceModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetPSTextureAddressMode(size_t textureIndex, TextureAddressMode newAddressMode)
	{
		if (PSTextureAddressMode[textureIndex] != newAddressMode) 
		{
			PSTextureAddressMode[textureIndex] = newAddressMode;
			PSSamplerModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetPSTextureFilterMode(size_t textureIndex, TextureFilterMode newFilterMode)
	{
		if (PSTextureFilterMode[textureIndex] != newFilterMode) 
		{
			PSTextureFilterMode[textureIndex] = newFilterMode;
			PSSamplerModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetCSTexture(size_t textureIndex, BSGraphics::Texture* newTexture)
	{
		ShaderResourceView* resourceView = newTexture ? newTexture->resourceView : nullptr;
		if (CSTexture[textureIndex] != resourceView) 
		{
			CSTexture[textureIndex] = resourceView;
			CSResourceModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetCSTextureAddressMode(size_t textureIndex, TextureAddressMode newAddressMode)
	{
		if (CSTextureAddressMode[textureIndex] != newAddressMode) 
		{
			CSTextureAddressMode[textureIndex] = newAddressMode;
			CSSamplerModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetCSTextureFilterMode(size_t textureIndex, TextureFilterMode newFilterMode)
	{
		if (CSTextureFilterMode[textureIndex] != newFilterMode) 
		{
			CSTextureFilterMode[textureIndex] = newFilterMode;
			CSSamplerModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetCSUAV(size_t textureIndex, UnorderedAccessView* newUAV)
	{
		if (CSUAV[textureIndex] != newUAV) 
		{
			CSUAV[textureIndex] = newUAV;
			CSUAVModifiedBits |= (1 << textureIndex);
		}
	}

	void RendererState::SetVertexDesc(uint64_t newVertexDesc)
	{
		if (vertexDesc != newVertexDesc)
		{
			vertexDesc = newVertexDesc;
			stateUpdateFlags.set(StateUpdateFlags::DirtyVertexDesc);
		}
	}

	void RendererState::SetTopology(Topology newTopology)
	{
		if (topology != newTopology) 
		{
			topology = newTopology;
			stateUpdateFlags.set(StateUpdateFlags::DirtyPrimitiveTopo);
		}
	}
}
