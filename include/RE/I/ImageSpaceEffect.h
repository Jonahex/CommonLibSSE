#pragma once

namespace RE
{
	class ImageSpaceEffectManager;
	class ImageSpaceEffectParam;
	class ImageSpaceTexture;

	class ImageSpaceEffect
	{
	public:
		class EffectInput;

		inline static constexpr auto RTTI = RTTI_ImageSpaceEffect;

		virtual ~ImageSpaceEffect();  // 00

		// add
		virtual void Unk_01(void* unk, ImageSpaceEffectParam* param);	// 01
		virtual void InitShaders(ImageSpaceEffectManager* manager);		// 02 - { return; }
		virtual void Unk_03(void);										// 03 - { return; }
		virtual void Unk_04(ImageSpaceEffectParam* param);				// 04 - { return; }
		virtual void Unk_05();											// 05 - { return; }
		virtual bool IsEnabled();										// 06
		virtual void Unk_07(ImageSpaceEffectParam* param);				// 07 - { return 0; }
		virtual void Unk_08(ImageSpaceEffectParam* param);				// 08 - { return 0; }
		virtual void Unk_09(ImageSpaceEffectParam* param);				// 09 - { return 0; }

		// members
		bool													isEnabled;				// 08
		NiTPrimitiveArray<ImageSpaceEffect*>					imageSpaceShaders;		// 10
		NiTPrimitiveArray<ImageSpaceEffectParam*>				params;					// 28
		NiTPrimitiveArray<ImageSpaceTexture*>					textures;				// 40
		NiTPrimitiveArray<ImageSpaceEffect::EffectInput*>		effectInputs;			// 58
		NiTPrimitiveArray<int>									unk70;					// 70
		bool													unk88;					// 88
	};
	static_assert(sizeof(ImageSpaceEffect) == 0x90);
}
