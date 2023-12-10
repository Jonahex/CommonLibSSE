#pragma once

#include "RE/B/BSShader.h"
#include "RE/B/BSShaderRenderTargets.h"
#include "RE/D/DepthStencilDepthModes.h"
#include "RE/N/NiPoint2.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiRect.h"
#include "RE/N/NiSourceTexture.h"
#include "RE/N/NiTransform.h"
#include "RE/T/TextureAddressModes.h"
#include "RE/T/TextureFilterModes.h"

#include "d3d11.h"
#include "DirectXMath.h"

struct ID3D11ShaderResourceView;
struct ID3D11UnorderedAccessView;

namespace RE
{
	namespace BSGraphics
	{
		struct __declspec(align(16)) ViewData
		{
			::DirectX::XMFLOAT4 viewUp;                            // 00
			::DirectX::XMFLOAT4 viewRight;                         // 10
			::DirectX::XMFLOAT4 viewDir;                           // 20
			::DirectX::XMMATRIX viewMat;                           // 30
			::DirectX::XMMATRIX projMat;                           // 70
			::DirectX::XMMATRIX viewProjMat;                       // B0
			::DirectX::XMMATRIX unkF0;                             // F0
			::DirectX::XMMATRIX viewProjMatrixUnjittered;          // 130
			::DirectX::XMMATRIX previousViewProjMatrixUnjittered;  // 170
			::DirectX::XMMATRIX projMatrixUnjittered;              // 1B0
			::DirectX::XMMATRIX unk1F0;                            // 1F0
			NiRect<float>       viewPort;                          // 230
			NiPoint2            viewDepthRange;                    // 240
			uint64_t            pad248;                            // 248
		};
		static_assert(sizeof(ViewData) == 0x250);

		enum class StateUpdateFlags : uint32_t
		{
			DirtyRenderTarget = 0x1,
			DirtyViewport = 0x2,
			DirtyDepthMode = 0x4,
			DirtyDepthStencilRefMode = 0x8,
			DirtyFillMode = 0x10,
			DirtyCullMode = 0x20,
			DirtyDepthBias = 0x40,
			DirtyAlphaBlend = 0x80,
			DirtyAlphaEnableTest = 0x100,
			DirtyAlphaTestRef = 0x200,
			DirtyVertexDesc = 0x400,
			DirtyPrimitiveTopo = 0x800,
			DirtyScissorMode = 0x1000,
		};

		enum class SetRenderTargetMode : uint32_t
		{
			Clear = 0x0,
			ClearDepth = 0x1,
			ClearStencil = 0x2,
			Restore = 0x3,
			NoClear = 0x4,
			ForceCopyRestore = 0x5,
			Init = 0x6,
		};

		enum class FillMode : uint32_t
		{
			Solid = 0x0,
			Wireframe = 0x1,
		};

		enum class CullMode : uint32_t
		{
			NoCulling = 0x0,
			CullBack = 0x1,
			CullFront = 0x2,
		};

		enum class ScissorMode : uint32_t
		{
			Disabled = 0x0,
			Enabled = 0x1,
		};

		enum class AlphaBlendMode : uint32_t
		{
			Mode0,
			Mode1,
			Mode2,
			Mode3,
			Mode4,
			Mode5,
			Mode6
		};

		// RenderTargetWriteMask = 0xF in all targets by default
		enum class AlphaBlendWriteMode : uint32_t
		{
			Mode0,  // 0x0 in target 0
			Mode1,  // 0x7 in target 0
			Mode2,  // default
			Mode3,  // 0x3 in target 0
			Mode4,  // 0xC in target 0
			Mode5,  // 0x1 in target 0
			Mode6,  // 0x2 in target 0
			Mode7,  // 0x4 in target 0
			Mode8,  // 0x8 in target 0
			Mode9,  // 0x4 in target 0, 0x7 in 1 target
			ModeA,  // 0x0 in target 1
			ModeB,  // 0x0 in target 1-7
			ModeC   // 0x0 in target 2-7
		};

		enum class DepthBiasMode : uint32_t
		{
			Mode0,  // 0 DepthBias, 0 SlopeScaledDepthBias
			Mode1,  // -3 DepthBias, -0.4 SlopeScaledDepthBias
			Mode2,  // -9 DepthBias, -1.2 SlopeScaledDepthBias
			Mode3,  // -3 DepthBias, -0.4 SlopeScaledDepthBias
			Mode4,  // 3 DepthBias, 0.4 SlopeScaledDepthBias
			Mode5,  // 6 DepthBias, 0.8 SlopeScaledDepthBias
			Mode6,  // -1 DepthBias, -0.65 SlopeScaledDepthBias
			Mode7,  // 0 DepthBias, 0 SlopeScaledDepthBias
			Mode8,  // -1 DepthBias, -0.65 SlopeScaledDepthBias
			Mode9,  // 0 DepthBias, 0 SlopeScaledDepthBias
			ModeA,  // -1 DepthBias, -0.65 SlopeScaledDepthBias
			ModeB,  // 0 DepthBias, 0 SlopeScaledDepthBias
		};

		using ShaderResourceView = ID3D11ShaderResourceView;
		using UnorderedAccessView = ID3D11UnorderedAccessView;
		using Viewport = D3D11_VIEWPORT;
		using Topology = D3D11_PRIMITIVE_TOPOLOGY;

		class RendererState
		{
		public:
			[[nodiscard]] static RendererState* GetSingleton() noexcept;

			ConstantGroup& GetVSConstantGroup(ConstantGroupLevel level);
			ConstantGroup& GetPSConstantGroup(ConstantGroupLevel level);

			void SetDepthStencilDepthMode(DepthStencilDepthMode newDepthStencilDepthMode);
			void SetFillMode(FillMode newFillMode);
			void SetCullMode(CullMode newCullMode);
			void SetDepthBiasMode(DepthBiasMode newDepthBiasMode);
			void SetScissorMode(ScissorMode newScissorMode);
			void SetAlphaBlendMode(AlphaBlendMode newAlphaBlendMode);
			void SetAlphaBlendWriteMode(AlphaBlendWriteMode newAlphaBlendWriteMode);
			void SetAlphaTestEnabled(bool newEnabled);
			void SetPSTexture(size_t textureIndex, BSGraphics::Texture* newTexture);
			void SetPSTextureAddressMode(size_t textureIndex, TextureAddressMode newAddressMode);
			void SetPSTextureFilterMode(size_t textureIndex, TextureFilterMode newFilterMode);
			void SetCSTexture(size_t textureIndex, BSGraphics::Texture* newTexture);
			void SetCSTextureAddressMode(size_t textureIndex, TextureAddressMode newAddressMode);
			void SetCSTextureFilterMode(size_t textureIndex, TextureFilterMode newFilterMode);
			void SetCSUAV(size_t textureIndex, UnorderedAccessView* newUAV);
			void SetVertexDesc(uint64_t newVertexDesc);
			void SetTopology(Topology newTopology);

			template<typename ValueType>
			void SetVSConstant(const ValueType& value, ConstantGroupLevel level, size_t index)
			{
				const int8_t offset = currentVertexShader->constantTable[index];
				*reinterpret_cast<ValueType*>((reinterpret_cast<float*>(currentVertexShader->constantBuffers[static_cast<size_t>(level)].data) + offset)) = value;
			}

			template <typename ValueType>
			void SetPSConstant(const ValueType& value, ConstantGroupLevel level, size_t index)
			{
				const int8_t offset = currentPixelShader->constantTable[index];
				*reinterpret_cast<ValueType*>((reinterpret_cast<float*>(currentPixelShader->constantBuffers[static_cast<size_t>(level)].data) + offset)) = value;
			}

			stl::enumeration<StateUpdateFlags, uint32_t>          stateUpdateFlags;                // 00
			uint32_t                                              PSResourceModifiedBits;          // 04
			uint32_t                                              PSSamplerModifiedBits;           // 08
			uint32_t                                              CSResourceModifiedBits;          // 0C
			uint32_t                                              CSSamplerModifiedBits;           // 10
			uint32_t                                              CSUAVModifiedBits;               // 14
			stl::enumeration<RENDER_TARGET, int32_t>              renderTargets[8];                // 18
			stl::enumeration<RENDER_TARGET_DEPTHSTENCIL, int32_t> depthStencil;                    // 38
			uint32_t                                              depthStencilSlice;               // 3C
			stl::enumeration<RENDER_TARGET_CUBEMAP, int32_t>      cubeMapRenderTarget;             // 40
			uint32_t                                              cubeMapRenderTargetView;         // 44
			stl::enumeration<SetRenderTargetMode, uint32_t>       setRenderTargetMode[8];          // 48
			stl::enumeration<SetRenderTargetMode, uint32_t>       setDepthStencilMode;             // 68
			stl::enumeration<SetRenderTargetMode, uint32_t>       setCubeMapRenderTargetMode;      // 6C
			Viewport                                              viewPort;                        // 70
			stl::enumeration<DepthStencilDepthMode, uint32_t>     depthStencilDepthMode;           // 88
			stl::enumeration<DepthStencilDepthMode, uint32_t>     referenceDepthStencilDepthMode;  // 8C
			uint32_t                                              depthStencilStencilMode;         // 90
			uint32_t                                              stencilRef;                      // 94
			stl::enumeration<FillMode, uint32_t>                  fillMode;                        // 98
			stl::enumeration<CullMode, uint32_t>                  cullMode;                        // 9C
			stl::enumeration<DepthBiasMode, uint32_t>             depthBiasMode;                   // A0
			stl::enumeration<ScissorMode, uint32_t>               scissorMode;                     // A4
			stl::enumeration<AlphaBlendMode, uint32_t>            alphaBlendMode;                  // A8
			uint32_t                                              alphaBlendAlphaToCoverage;       // AC
			stl::enumeration<AlphaBlendWriteMode, uint32_t>       alphaBlendWriteMode;             // B0
			bool                                                  alphaTestEnabled;                // B4
			float                                                 alphaTestRef;                    // B8
			stl::enumeration<TextureAddressMode, uint32_t>        PSTextureAddressMode[16];        // BC
			stl::enumeration<TextureFilterMode, uint32_t>         PSTextureFilterMode[16];         // FC
			ShaderResourceView*                                   PSTexture[16];                   // 140
			stl::enumeration<TextureAddressMode, uint32_t>        CSTextureAddressMode[16];        // 1C0
			stl::enumeration<TextureFilterMode, uint32_t>         CSTextureFilterMode[16];         // 200
			ShaderResourceView*                                   CSTexture[16];                   // 240
			uint32_t                                              CSTextureMinLodMode[16];         // 2C0
			UnorderedAccessView*                                  CSUAV[8];                        // 300
			uint64_t                                              vertexDesc;                      // 340
			VertexShader*                                         currentVertexShader;             // 348
			PixelShader*                                          currentPixelShader;              // 350
			stl::enumeration<Topology, uint32_t>                  topology;                        // 358
			NiPoint3                                              posAdjust;                       // 35C
			NiPoint3                                              previousPosAdjust;               // 368
			uint64_t                                              pad378;                          // 378
			ViewData                                              cameraData;                      // 380
			uint32_t                                              alphaBlendModeExtra;             // 5D0
		};
		static_assert(sizeof(RendererState) == 0x5E0);
	}
}
