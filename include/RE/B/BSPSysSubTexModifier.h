#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class BSPSysSubTexModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysSubTexModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysSubTexModifier;

		~BSPSysSubTexModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25
		
		// members
		float startFrame;           // 30
		float startFrameFudge;      // 34
		float endFrame;             // 38
		float loopStartFrame;       // 3C
		float loopStartFrameFudge;  // 40
		float frameCount;           // 44
		float frameCountFudge;      // 48
	};
	static_assert(sizeof(BSPSysSubTexModifier) == 0x50);
}
