#pragma once

#include "RE/B/BSLight.h"
#include "RE/N/NiAccumulator.h"

namespace RE
{
	class NiBackToFrontAccumulator : public NiAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBackToFrontAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiBackToFrontAccumulator;

		~NiBackToFrontAccumulator() override;  // 00

		// override (NiAccumulator)
		const NiRTTI* GetRTTI() const override;                                        // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;               // 17
		void          LoadBinary(NiStream& a_stream) override;                         // 18
		void          LinkObject(NiStream& a_stream) override;                         // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                // 1A
		void          SaveBinary(NiStream& a_stream) override;                         // 1B
		bool          IsEqual(NiObject* a_object) override;                            // 1C
		void          Render(RenderFlags renderFlags) override;                        // 26
		void          RegisterObjects(const BSTArray<BSGeometry*>& objects) override;  // 27

		// members
		BSLight::ShapeList shapeList;    // 18
		BSGeometry**       object;       // 38
		float*             depths;       // 40
		int                currentItem;  // 48
	};
	static_assert(sizeof(NiBackToFrontAccumulator) == 0x50);
}
