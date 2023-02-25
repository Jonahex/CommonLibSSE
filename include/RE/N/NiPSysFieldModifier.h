#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiAVObject;

	class NiPSysFieldModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysFieldModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysFieldModifier;

		~NiPSysFieldModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                        // 1D
		
		void SetMaxDistance(float aMaxDistance)
		{
			maxDistance = aMaxDistance;
			maxDistanceSquared = aMaxDistance * aMaxDistance;
		}

		// members
		NiAVObject* fieldObject;         // 30
		float       magnitude;           // 38
		float       attenuation;         // 3C
		bool        useMaxDistance;      // 40
		float       maxDistance;         // 44
		float       maxDistanceSquared;  // 48
	};
	static_assert(sizeof(NiPSysFieldModifier) == 0x50);
}
