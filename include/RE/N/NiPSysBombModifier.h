#pragma once

#include "RE/N/NiPSysModifier.h"

namespace RE
{
	class NiPSysBombModifier : public NiPSysModifier
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysBombModifier;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysBombModifier;

		enum class DecayType
		{
			None = 0x0,
			Linear = 0x1,
			Exponential = 0x2,
		};

		enum class SymmetryType
		{
			Spherical = 0x0,
			Cylindrical = 0x1,
			Planar = 0x2,
		};

		~NiPSysBombModifier() override;  // 00

		// override (NiPSysModifier)
		const NiRTTI* GetRTTI() const override;                                                                                                  // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                                                         // 17
		void          LoadBinary(NiStream& a_stream) override;                                                                                   // 18
		void          LinkObject(NiStream& a_stream) override;                                                                                   // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                                          // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                                   // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                                      // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                                        // 1D
		bool          Update(float a_time, NiPSysData* a_particleData, NiPoint3* a_position, NiPoint3* a_radii, NiColorA* a_rotation) override;  // 25

		// members
		NiNode*                                  bombObject;    // 30
		NiPoint3                                 bombAxis;      // 38
		float                                    decay;         // 44
		float                                    acceleration;  // 48
		stl::enumeration<DecayType, uint32_t>    decayType;     // 4C
		stl::enumeration<SymmetryType, uint32_t> symmetryType;  // 50
	};
	static_assert(sizeof(NiPSysBombModifier) == 0x58);
}
