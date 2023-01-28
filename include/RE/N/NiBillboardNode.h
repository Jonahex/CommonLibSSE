#pragma once

#include "RE/B/BSNiNode.h"

namespace RE
{
	class NiBillboardNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBillboardNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiBillboardNode;

		enum class BillboardMode : uint16_t
		{
			AlwaysFaceCamera = 0,
			RotateAboutUp = 1,
			RigidFaceCamera = 2,
			AlwaysFaceCenter = 3,
			RigidFaceCenter = 4,
			BSRotateAboutUp = 5,
			RotateAboutUp2 = 9,
		};

		~NiBillboardNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;                                                         // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                // 17
		void          LoadBinary(NiStream& a_stream) override;                                          // 18
		void          LinkObject(NiStream& a_stream) override;                                          // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                 // 1A
		void          SaveBinary(NiStream& a_stream) override;                                          // 1B
		bool          IsEqual(NiObject* a_object) override;                                             // 1C                                // 2E
		void          UpdateWorldBound() override;                                                      // 2F
		void          UpdateWorldData(NiUpdateData* a_data) override;                                   // 30
		void          OnVisible(NiCullingProcess& a_process) override;                                  // 34

		// members
		stl::enumeration<BillboardMode, uint16_t>       billboardMode;    // 128
	};
	static_assert(sizeof(NiBillboardNode) == 0x130);
}
