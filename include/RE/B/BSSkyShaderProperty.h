#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSShaderProperty.h"

namespace RE
{
	class BSSkyShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSkyShaderProperty;
		inline static auto           Ni_RTTI = NiRTTI_BSSkyShaderProperty;
		inline static auto           VTABLE = VTABLE_BSSkyShaderProperty;

		enum class SkyObjectType
		{
			Sun = 0x0,
			SunGlare = 0x1,
			Atmosphere = 0x2,
			Clouds = 0x3,
			SkyQuad = 0x4,
			Stars = 0x5,
			Moon = 0x6,
			MoonShadow = 0x7,
		};

		~BSSkyShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*                          GetRTTI() const override;                                                                                      // 02
		NiObject*                              CreateClone(NiCloningProcess& a_cloning) override;                                                             // 17
		void                                   LoadBinary(NiStream& a_stream) override;                                                                       // 18
		void                                   LinkObject(NiStream& a_stream) override;                                                                       // 19
		bool                                   RegisterStreamables(NiStream& a_stream) override;                                                              // 1A
		void                                   SaveBinary(NiStream& a_stream) override;                                                                       // 1B
		bool                                   IsEqual(NiObject* a_object) override;                                                                          // 1C
		void                                   PostLinkObject(NiStream& a_stream) override;                                                                   // 1E
		RenderPassArray*                       GetRenderPasses(BSGeometry* a_geometry, RenderMode a_renderMode, BSShaderAccumulator* a_accumulator) override; // 2A
		std::int32_t                           ForEachTexture(ForEachVisitor& a_visitor) override;                                                            // 33
		virtual std::int32_t                   QShader() override;                                                                                            // 35
		[[nodiscard]] virtual NiSourceTexture* GetBaseTexture() override;                                                                                     // 37

		RenderPassArray* GetRenderPassesImpl(BSGeometry* geometry, RenderMode renderMode, BSShaderAccumulator* accumulator);

		// members
		NiColorA                              color;              // 88
		NiPointer<NiSourceTexture>            baseTexture;        // 98
		NiPointer<NiSourceTexture>            blendTexture;       // A0
		NiPointer<NiSourceTexture>            noiseGradTexture;   // A8
		BSFixedString                         baseTexturePath;    // B0
		float                                 blendValue;         // B8
		uint16_t                              cloudLayer;         // BC
		bool                                  fadeSecondTexture;  // BE
		REX::EnumSet<SkyObjectType, uint32_t> objectType;         // C0
	};
	static_assert(sizeof(BSSkyShaderProperty) == 0xC8);
}
