#pragma once

#include "RE/N/NiPSysModifier.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiPSysEmitter : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysEmitter;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysEmitter;

		~NiPSysEmitter() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25

		// add
		virtual void Unk2A(float unk00, int unk01, float* unk02);                                    // 2A
		virtual void GetEmitPositionDirection(NiPoint3& emitPosition, NiPoint3& emitDirection) = 0;  // 2B
		
		// members
		uint32_t unk30;                 // 30
		float    speed;                 // 34
		float    speedVariation;        // 38
		float    declination;           // 3C
		float    declinationVariation;  // 40
		float    planarAngle;           // 44
		float    planarAngleVariation;  // 48
		NiColorA initialColor;          // 4C
		float    initialRadius;         // 5C
		float    radiusVariation;       // 60
		float    lifeSpan;              // 64
		float    lifeSpanVariation;     // 68
		uint32_t unk6c;                 // 6C
	};
	static_assert(sizeof(NiPSysEmitter) == 0x70);
}
