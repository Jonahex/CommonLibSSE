#pragma once

#include "RE/N/NiAlphaAccumulator.h"

namespace RE
{
	class BSBatchRenderer;
	class ShadowSceneNode;

	enum class RenderMode : uint32_t
	{
		Depth = 0xC,
		SpotShadowmap = 0xD,
		DirectionalShadowmap = 0xE,
		OmnidirectionalShadowmap = 0xF,
		Unk17 = 0x11,
		LocalMap = 0x12,
		LocalMapFogOfWar = 0x13,
		FirstPersonView = 0x16,
		BloodSplatter = 0x17,
		DebugColor = 0x1B,
		PrecipitationOcclusionMap = 0x1C,
	};

	class BSShaderAccumulator : public NiAlphaAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSShaderAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSShaderAccumulator;

		~BSShaderAccumulator() override;  // 00

		// override (NiAlphaAccumulator)
		void SetCamera(NiCamera* inCamera) override;    // 25
		void Render(RenderFlags renderFlags) override;  // 26
		void Unk28(void) override;                      // 28
		void Unk29(void) override;                      // 29

		// add
		virtual void RenderDispatch(RenderFlags renderFlags);  // 2A
		virtual void Unk2B(RenderFlags renderFlags);           // 2B
		virtual void Unk2C(void);                              // 2C

		// members
		uint32_t         unk58;                  // 58
		bool             unk5C;                  // 5C
		uint32_t         unk60;                  // 60
		bool             unk64;                  // 64
		float            unk68;                  // 68
		uint64_t         unk70;                  // 70
		uint64_t         unk78;                  // 78
		uint32_t         unk80;                  // 80
		bool             unk84;                  // 84
		uint64_t         unk88;                  // 88
		uint64_t         unk90;                  // 90
		uint32_t         unk98;                  // 98
		bool             unk9C;                  // 9C
		uint64_t         unkA0;                  // A0
		uint64_t         unkA8;                  // A8
		uint32_t         unkB0;                  // B0
		bool             unkB4;                  // B4
		bool             unkB5;                  // B5
		uint16_t         unkB6;                  // B6
		bool             unkB8;                  // B8
		bool             unkB9;                  // B9
		bool             unkBA;                  // BA
		bool             unkBB;                  // BB
		uint32_t         unkBC;                  // BC
		uint64_t         unkC0;                  // C0
		uint64_t         unkC8;                  // C8
		uint64_t         unkD0;                  // D0
		uint32_t         unkD8;                  // D8
		uint64_t         unkE0;                  // E0
		uint32_t         unkE8;                  // E8
		uint64_t         unkF0;                  // F0
		uint64_t         unkF8;                  // F8
		uint64_t         unk100;                 // 100
		uint64_t         unk108;                 // 108
		uint32_t         unk110;                 // 110
		bool             unk114;                 // 114
		uint64_t         unk118;                 // 118
		uint64_t         unk120;                 // 120
		bool             firstPerson;            // 128
		bool             unk129;                 // 129
		bool             unk12A;                 // 12A
		bool             unk12B;                 // 12B
		bool             drawDecals;             // 12C
		bool             unk12D;                 // 12D
		bool             unk12E;                 // 12E
		BSBatchRenderer* batchRenderer;          // 130
		uint32_t         currentPass;            // 134
		uint32_t         currentBucket;          // 138
		bool             currentActive;          // 140
		ShadowSceneNode* activeShadowSceneNode;  // 148
		RenderMode       renderMode;             // 150
		uint64_t         unk158;                 // 158
		uint64_t         unk160;                 // 160
		uint32_t         unk168;                 // 168
		NiPoint3         eyePosition;            // 16C
		bool             unk178;                 // 178
	};
	static_assert(sizeof(BSShaderAccumulator) == 0x180);
}
