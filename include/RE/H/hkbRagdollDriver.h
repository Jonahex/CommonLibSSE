#pragma once

#include "RE/H/hkbWorldFromModelModeData.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkaRagdollInstance;
	class hkpRigidBody;

	class hkbRagdollDriver : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRagdollDriver;
		inline static constexpr auto VTABLE = VTABLE_hkbRagdollDriver;

		~hkbRagdollDriver() override;  // 00

		// members
		float                            ragdollBlendOutTime;                          // 10
		hkbWorldFromModelModeData        worldFromModelModeData;                       // 14
		bool                             autoAddRemoveRagdollToWorld;                  // 1C
		bool                             useAsynchronousStepping;                      // 1D
		hkQsTransform                    lastWorldFromModel;                           // 20
		hkbWorldFromModelModeData        worldFromModelModeDataInternal;               // 50
		hkArray<int32_t>                 reportingWhenKeyframed;                       // 58
		std::uint32_t                    unk68;                                        // 68
		hkPointerMap<hkpRigidBody*, int> attachedRigidBodyToIndexMap;                  // 70
		hkbCharacter*                    character;                                    // 80
		hkaRagdollInstance*              ragdoll;                                      // 88
		hkQsTransform*                   ragdollPoseWS;                                // 90
		void*                            ragdollPoweredController;                     // 98
		void*                            ragdollRigidBodyController;                   // A0
		hkQsTransform*                   ragdollPoseHiResLocal;                        // A8
		hkQsTransform*                   lastPoseLocal;                                // B0
		int32_t                          lastNumPoseLocal;                             // B8
		float                            timeRigidBodyControllerActive;                // BC
		float                            ragdollBlendOutTimeElapsed;                   // C0
		std::uint32_t                    unkC4;                                        // C4
		std::uint64_t                    unkC8;                                        // C8
	};
	static_assert(sizeof(hkbRagdollDriver) == 0xD0);
}
