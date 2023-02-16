#pragma once

#include "RE/N/NiPSysVolumeEmitter.h"

namespace RE
{
	class NiPSysCylinderEmitter : public NiPSysVolumeEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysCylinderEmitter;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysCylinderEmitter;

		~NiPSysCylinderEmitter() override;  // 00

		// override (NiPSysVolumeEmitter)
		const NiRTTI* GetRTTI() const override;                                                                                               // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                      // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                       // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                   // 1C - { return false; }
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                     // 1D
		void          GetFinalEmitPositionDirection(NiPoint3& emitPosition, const NiTransform& transform, NiPoint3& emitDirection) override;  // 2D

		// members
		float radius;  // 78
		float height;  // 7C
	};
	static_assert(sizeof(NiPSysCylinderEmitter) == 0x80);
}
