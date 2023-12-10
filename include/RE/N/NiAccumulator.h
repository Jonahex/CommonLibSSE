#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class NiCamera;

	enum class RenderFlags
	{
		AlphaBlendEnabled = 0x4,
		Cubemap = 0x8,
		Unk20 = 0x20,
		Unk40 = 0x40,
		Unk80 = 0x80,
		VolumetricLightingShadowmap = 0x100,
		Unk200 = 0x200,
		Shadowmap = 0x400,
	};

	class NiAccumulator : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAccumulator;

		~NiAccumulator() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                            // 02
		void          LoadBinary(NiStream& a_stream) override;             // 18
		void          LinkObject(NiStream& a_stream) override;             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;    // 1A
		void          SaveBinary(NiStream& a_stream) override;             // 1B
		bool          IsEqual(NiObject* a_object) override;                // 1C

		// add
		virtual void SetCamera(NiCamera* inCamera);                              // 25
		virtual void Render(RenderFlags renderFlags);                            // 26
		virtual void RegisterObjects(const BSTArray<BSGeometry*>& objects) = 0;  // 27
		virtual void Unk28(void);                                                // 28
		virtual void Unk29(void);                                                // 29

		// members
		NiCamera* camera;  // 10
	};
	static_assert(sizeof(NiAccumulator) == 0x18);
}
