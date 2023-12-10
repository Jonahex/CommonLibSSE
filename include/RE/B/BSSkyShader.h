#pragma once

#include "RE/B/BSShader.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint2.h"

namespace RE
{
	class BSSkyShader : public BSShader
	{
	public:
		enum class LocalTechnique
		{
			SunOcclude = 0,
			SunGlare = 1,
			MoonAndStarsMask = 2,
			Stars = 3,
			Clouds = 4,
			CloudsLerp = 5,
			CloudsFade = 6,
			Texture = 7,
			Sky = 8,
		};

		enum class TextureSlot
		{
			Base = 0,
			Blend = 1,
			NoiseGrad = 2,
		};

		static BSSkyShader* GetSingleton()
		{
			REL::Relocation<BSSkyShader**> singleton{ RELOCATION_ID(528198, 415143) };
			return *singleton;
		}

		static LocalTechnique GetLocalTechnique(uint32_t globalTechnique);
		static LocalTechnique GetVertexTechnique(LocalTechnique localTechnique);
		static LocalTechnique GetPixelTechnique(LocalTechnique localTechnique);

		static NiColorA& GetAtmosphereBlendColor(size_t colorIndex);
		static NiPoint2& GetCloudLayerOffset(size_t cloudLayerIndex);

		~BSSkyShader() override;  // 00

		// override (BSShader)
		bool SetupTechnique(std::uint32_t globalTechnique) override;           // 02
		void RestoreTechnique(std::uint32_t globalTechnique) override;         // 03
		void SetupGeometry(BSRenderPass* pass, RenderFlags flags) override;    // 06
		void RestoreGeometry(BSRenderPass* pass, RenderFlags flags) override;  // 07

		bool SetupTechniqueImpl(std::uint32_t globalTechnique);
		void RestoreTechniqueImpl(std::uint32_t globalTechnique);
		void SetupGeometryImpl(BSRenderPass* pass, RenderFlags flags);
		void RestoreGeometryImpl(BSRenderPass* pass, RenderFlags flags);
	};
	static_assert(sizeof(BSSkyShader) == 0x90);
}
