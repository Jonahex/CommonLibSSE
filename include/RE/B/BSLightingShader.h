#pragma once

#include "RE/B/BSShader.h"

namespace RE
{
	class BSLightingShader : public BSShader
	{
	public:
		enum class Flags
		{
			Vc = 1 << 0,
			Skinned = 1 << 1,
			ModelSpaceNormals = 1 << 2,
			// flags 3 to 8 are unused
			Specular = 1 << 9,
			SoftLighting = 1 << 10,
			RimLighting = 1 << 11,
			BackLighting = 1 << 12,
			ShadowDir = 1 << 13,
			DefShadow = 1 << 14,
			ProjectedUv = 1 << 15,
			AnisoLighting = 1 << 16,
			AmbientSpecular = 1 << 17,
			WorldMap = 1 << 18,
			BaseObjectIsSnow = 1 << 19,
			DoAlphaTest = 1 << 20,
			Snow = 1 << 21,
			CharacterLight = 1 << 22,
			AdditionalAlphaMask = 1 << 23,
		};

		enum class LocalTechnique
		{
			None = 0,
			Envmap = 1,
			Glowmap = 2,
			Parallax = 3,
			Facegen = 4,
			FacegenRgbTint = 5,
			Hair = 6,
			ParallaxOcc = 7,
			MtLand = 8,
			LodLand = 9,
			Snow = 10,  // unused
			MultiLayerParallax = 11,
			TreeAnim = 12,
			LodObjects = 13,
			MultiIndexSparkle = 14,
			LodObjectsHd = 15,
			Eye = 16,
			Cloud = 17,  // unused
			LodLandNoise = 18,
			MtLandLodBlend = 19,
		};

		static BSLightingShader* GetSingleton()
		{
			REL::Relocation<BSLightingShader**> singleton{ RELOCATION_ID(528150, 415094) };
			return *singleton;
		}

		~BSLightingShader() override;  // 00

		// override (BSShader)
		bool SetupTechnique(std::uint32_t globalTechnique) override;           // 02
		void RestoreTechnique(std::uint32_t globalTechnique) override;         // 03
		void SetupGeometry(BSRenderPass* pass, RenderFlags flags) override;    // 06
		void RestoreGeometry(BSRenderPass* pass, RenderFlags flags) override;  // 07
	};
	static_assert(sizeof(BSLightingShader) == 0x90);
}
