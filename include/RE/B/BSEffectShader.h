#pragma once

#include "RE/B/BSShader.h"

namespace RE
{
	class BSEffectShader : public BSShader
	{
	public:
		enum class Flags
		{
			Vc = 1 << 0,
			TexCoord = 1 << 1,
			TexCoordIndex = 1 << 2,
			Skinned = 1 << 3,
			Normals = 1 << 4,
			BinormalTangent = 1 << 5,
			Texture = 1 << 6,
			IndexedTexture = 1 << 7,
			Falloff = 1 << 8,
			AddBlend = 1 << 10,
			MultBlend = 1 << 11,
			Particles = 1 << 12,
			StripParticles = 1 << 13,
			Blood = 1 << 14,
			Membrane = 1 << 15,
			Lighting = 1 << 16,
			ProjectedUv = 1 << 17,
			Soft = 1 << 18,
			GrayscaleToColor = 1 << 19,
			GrayscaleToAlpha = 1 << 20,
			IgnoreTexAlpha = 1 << 21,
			MultBlendDecal = 1 << 22,
			AlphaTest = 1 << 23,
			SkyObject = 1 << 24,
			MsnSpuSkinned = 1 << 25,
			MotionVectorsNormals = 1 << 26,
		};

		static BSEffectShader* GetSingleton()
		{
			REL::Relocation<BSEffectShader**> singleton{ RELOCATION_ID(528216, 415166) };
			return *singleton;
		}

		~BSEffectShader() override;  // 00

		// override (BSShader)
		bool SetupTechnique(std::uint32_t globalTechnique) override;           // 02
		void RestoreTechnique(std::uint32_t globalTechnique) override;         // 03
		void SetupGeometry(BSRenderPass* pass, RenderFlags flags) override;    // 06
		void RestoreGeometry(BSRenderPass* pass, RenderFlags flags) override;  // 07
	};
	static_assert(sizeof(BSEffectShader) == 0x90);
}
