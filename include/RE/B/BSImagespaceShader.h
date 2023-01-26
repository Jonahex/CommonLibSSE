#pragma once

#include "RE/B/BSShader.h"
#include "RE/I/ImageSpaceEffect.h"

namespace RE
{
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
		virtual void Unk_0E(void);  // 0E

		// members
		BSFixedString			name;					// 120
		BSFixedString			unk128;					// 128
		std::uint64_t			unk130;					// 130
		BSTArray<BSFixedString> vsConstantNames;		// 138
		BSTArray<BSFixedString> psConstantNames;        // 150
		BSTArray<BSFixedString> samplerNames;			// 158
		std::uint64_t			unk180;					// 180
		std::uint64_t			unk188;					// 188
		std::uint64_t			unk190;					// 190
		std::uint64_t			unk198;					// 198
		std::uint64_t			unk1A0;					// 1A0
	};
	static_assert(sizeof(BSImagespaceShader) == 0x1A8);
}
