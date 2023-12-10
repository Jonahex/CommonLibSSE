#pragma once

#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSShaderPropertyLightData.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSLightingShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSLightingShaderProperty;

		~BSLightingShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*          GetRTTI() const override;                                                                                                          // 02
		NiObject*              CreateClone(NiCloningProcess& a_cloning) override;                                                                                 // 17
		void                   LoadBinary(NiStream& a_stream) override;                                                                                           // 18
		void                   LinkObject(NiStream& a_stream) override;                                                                                           // 19
		bool                   RegisterStreamables(NiStream& a_stream) override;                                                                                  // 1A
		void                   SaveBinary(NiStream& a_stream) override;                                                                                           // 1B
		bool                   IsEqual(NiObject* a_object) override;                                                                                              // 1C - { return false; }
		void                   PostLinkObject(NiStream& a_stream) override;                                                                                       // 1E
		bool                   SetupGeometry(BSGeometry* a_geometry) override;                                                                                    // 27
		bool                   FinishSetupGeometry(BSGeometry* a_geometry) override;                                                                              // 28
		RenderPassArray*       GetRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;                           // 2A
		RenderPassArray*       GetDepthAndShadowmapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;          // 2B
		RenderPassArray*       GetLocalMapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;                   // 2C
		RenderPassArray*       GetPrecipitationOcclusionMapRenderPasses(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator) override;  // 2D
		BSRenderPass*          GetDepthRenderPass(BSGeometry* geometry) override;                                                                                 // 2F
		bool                   CanMerge(const BSShaderProperty* a_other) override;                                                                                // 30
		void                   SetMaterialAlpha(float a_alpha) override;                                                                                          // 31
		float                  QMaterialAlpha() override;                                                                                                         // 32
		std::int32_t           ForEachTexture(ForEachVisitor& a_visitor) override;                                                                                // 33
		void                   DoClearRenderPasses() override;                                                                                                    // 34
		std::int32_t           QShader() override;                                                                                                                // 35 - { return 11; }
		NiSourceTexture*       GetBaseTexture() override;                                                                                                         // 37 - { return diffuseTexture }
		bool                   AcceptsEffectData() const override;                                                                                                // 39 - { return !(flags & kRefraction) && !(flags & kTempRefraction); }
		void                   Unk_3B(void) override;                                                                                                             // 3B
		std::uint32_t          DetermineUtilityShaderDecl() override;                                                                                             // 3D
		BSShaderMaterial::Type GetMaterialType() override;                                                                                                        // 3E - { return 2; }

		RenderPassArray* GetRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator);
		RenderPassArray* GetDepthAndShadowmapRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator);
		RenderPassArray* GetLocalMapRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator);
		RenderPassArray* GetPrecipitationOcclusionMapRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator);

		void CopyMembers(BSLightingShaderProperty* a_other);

		// members
		RenderPassArray           shadowmapRenderPassLists[3];              // 088
		RenderPassArray           shadowmaskRenderPassList;                 // 0B8
		RenderPassArray           precipitationOcclusionMapRenderPassList;  // 0C8
		RenderPassArray           unk0D8;                                   // 0D0
		BSRenderPass*             unk0E8;                                   // 0E8
		NiColor*                  emissiveColor;                            // 0F0
		float                     emissiveMult;                             // 0F8
		float                     forcedDarkness;                           // 0FC - unused
		float                     specularLODFade;                          // 100
		float                     envmapLODFade;                            // 104
		float                     unk108;                                   // 108
		NiColorA                  projectedUVParams;                        // 10C
		NiColorA                  projectedUVColor;                         // 11C
		std::int32_t              unk12C;                                   // 12C
		std::uint16_t             unk130;                                   // 130
		std::uint8_t              currentShadowmapRenderPassListIndex;      // 132
		std::uint8_t              previousShadowmapRenderPassListIndex;     // 133
		std::uint32_t             unk134;                                   // 134
		BSShaderPropertyLightData lightDataInstance;                        // 138
	};
	static_assert(sizeof(BSLightingShaderProperty) == 0x160);
}
