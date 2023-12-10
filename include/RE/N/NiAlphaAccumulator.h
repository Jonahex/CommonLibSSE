#pragma once

#include "RE/N/NiBackToFrontAccumulator.h"

namespace RE
{
	class NiAlphaAccumulator : public NiBackToFrontAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAlphaAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiAlphaAccumulator;

		~NiAlphaAccumulator() override;  // 00

		// override (NiBackToFrontAccumulator)
		const NiRTTI* GetRTTI() const override;                                        // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;               // 17
		void          LoadBinary(NiStream& a_stream) override;                         // 18
		void          LinkObject(NiStream& a_stream) override;                         // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                // 1A
		void          SaveBinary(NiStream& a_stream) override;                         // 1B
		bool          IsEqual(NiObject* a_object) override;                            // 1C
		void          RegisterObjects(const BSTArray<BSGeometry*>& objects) override;  // 27

		// members
		bool observeNoSortHint;   // 50
		bool sortByClosestPoint;  // 51
		bool interfaceSort;       // 52
	};
	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
}
