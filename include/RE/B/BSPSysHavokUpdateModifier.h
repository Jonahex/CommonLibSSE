#pragma once

#include "RE/N/NiPSysMeshUpdateModifier.h"

namespace RE
{
	class BSPSysHavokUpdateModifier : public NiPSysMeshUpdateModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPSysHavokUpdateModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSPSysHavokUpdateModifier;

		~BSPSysHavokUpdateModifier() override;  // 00
		
		// override (NiPSysMeshUpdateModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                        // 1D
		void          PostLinkObject(NiStream& a_stream) override;                                                                               // 1E
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25
		void          Initialize(NiPSysData* a_particleData, std::uint16_t, NiPoint3*) override;                                                 // 26

		// members
		NiPointer<NiObject>       unk48;     // 48
		NiPointer<NiPSysModifier> modifier;  // 50
	};
	static_assert(sizeof(BSPSysHavokUpdateModifier) == 0x58);
}
