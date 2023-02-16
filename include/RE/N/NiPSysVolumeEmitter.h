#pragma once

#include "RE/N/NiPSysEmitter.h"

namespace RE
{
	class NiTransform;

	class NiPSysVolumeEmitter : public NiPSysEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysVolumeEmitter;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysVolumeEmitter;

		~NiPSysVolumeEmitter() override;  // 00

		// override (NiPSysEmitter)
		const NiRTTI* GetRTTI() const override;                                                            // 02
		void          LoadBinary(NiStream& a_stream) override;                                             // 18
		void          LinkObject(NiStream& a_stream) override;                                             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                    // 1A
		void          SaveBinary(NiStream& a_stream) override;                                             // 1B
		bool          IsEqual(NiObject* a_object) override;                                                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                  // 1D
		void          GetEmitPositionDirection(NiPoint3& emitPosition, NiPoint3& emitDirection) override;  // 2B

		// add
		virtual void SetEmitter(NiNode* a_emitter);                                                                                     // 2C
		virtual void GetFinalEmitPositionDirection(NiPoint3& emitPosition, const NiTransform& transform, NiPoint3& emitDirection) = 0;  // 2D
		
		// members
		NiNode* emitter;  // 70
	};
	static_assert(sizeof(NiPSysVolumeEmitter) == 0x78);
}
