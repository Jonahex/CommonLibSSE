#pragma once

#include "RE/B/BSShader.h"
#include "RE/I/ImageSpaceEffect.h"

namespace RE
{
	class BSComputeShader;

	class BSImagespaceShader :
		public BSShader,         // 000
		public ImageSpaceEffect  // 090
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSImagespaceShader;

		~BSImagespaceShader() override;  // 00

		// override (BSShader)
		void     InitShaders(ImageSpaceEffectManager* manager) override;  // 02
		void     Unk_03(void) override;                                   // 03
		bool     IsEnabled(void) override;                                // 06
		void     Unk_07(ImageSpaceEffectParam* param) override;           // 07
		void     Unk_09(ImageSpaceEffectParam* param) override;           // 09

		// add
		virtual void Unk_0A(void);  // 0A - { return; }
		virtual void Unk_0B(void);  // 0B - { return; }
		virtual void Unk_0C(void);  // 0C
		virtual void Unk_0D(void);  // 0D
		virtual void LoadShaders();  // 0E

		// members
		BSFixedString           name;                // 120
		BSFixedString           originalShaderName;  // 128
		std::uint64_t           unk130;              // 130
		BSTArray<BSFixedString> vsConstantNames;     // 138
		BSTArray<BSFixedString> psConstantNames;     // 150
		BSTArray<BSFixedString> samplerNames;        // 158
		BSTArray<BSFixedString> unk180;              // 180
		BSComputeShader*        computeShader;       // 198
		bool                    unk1A0;              // 1A0
		bool                    isComputeShader;     // 1A1
	};
	static_assert(sizeof(BSImagespaceShader) == 0x1A8);
}
