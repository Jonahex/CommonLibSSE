#pragma once

#include "RE/N/NiPSysEmitter.h"
#include "RE/N/NiTArray.h"

namespace RE
{
	class NiPSysMeshEmitter : public NiPSysEmitter
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiPSysMeshEmitter;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiPSysMeshEmitter;

		enum class VelocityType
		{
			Normals = 0x0,
			Random = 0x1,
			Direction = 0x2,
		};

		enum class EmitFrom
		{
			Vertices = 0x0,
			FaceCenter = 0x1,
			EdgeCenter = 0x2,
			FaceSurface = 0x3,
			EdgeSurface = 0x4,
		};

		~NiPSysMeshEmitter() override;  // 00

		// override (NiPSysEmitter)
		const NiRTTI* GetRTTI() const override;                                                            // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                   // 17
		void          LinkObject(NiStream& a_stream) override;                                             // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                    // 1A
		void          SaveBinary(NiStream& a_stream) override;                                             // 1B
		bool          IsEqual(NiObject* a_object) override;                                                // 1C
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                  // 1D
		void          GetEmitPositionDirection(NiPoint3& emitPosition, NiPoint3& emitDirection) override;  // 2B

		// members
		NiTObjectArray<NiPointer<BSTriShape>>    emitterMeshes;        // 78
		NiTObjectArray<NiPointer<BSGeometry>>    unk88;                // 88
		stl::enumeration<VelocityType, uint32_t> initialVelocityType;  // A0
		stl::enumeration<EmitFrom, uint32_t>     emissionType;         // A4
		NiPoint3                                 emissionAxis;         // A8
	};
	static_assert(sizeof(NiPSysMeshEmitter) == 0xB8);
}
