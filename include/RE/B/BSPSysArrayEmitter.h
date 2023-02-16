#pragma once

#include "RE/N/NiPSysVolumeEmitter.h"

namespace RE
{
	class BSPSysArrayEmitter : public NiPSysVolumeEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysArrayEmitter;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysArrayEmitter;

		~BSPSysArrayEmitter() override;  // 00

		// override (NiPSysVolumeEmitter)
		const NiRTTI* GetRTTI() const override;                                                                                               // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                      // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                       // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                   // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                     // 1D
		void          PostLinkObject(NiStream& a_stream) override;                                                                            // 1E
		void          SetEmitter(NiNode* a_emitter) override;                                                                                 // 2C
		void          GetFinalEmitPositionDirection(NiPoint3& emitPosition, const NiTransform& transform, NiPoint3& emitDirection) override;  // 2D

		// members
		uint64_t unk78;  // 78
		uint64_t unk80;  // 80
		uint64_t unk88;  // 88
		uint64_t unk90;  // 90
	};
	static_assert(sizeof(BSPSysArrayEmitter) == 0x98);
}
