#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/bhkEntity.h"
#include "RE/H/hkMatrix3.h"
#include "RE/H/hkpMaterial.h"
#include "RE/H/hkpMotion.h"

namespace RE
{
	class hkAabb;
	class hkLocalFrame;
	class hkpShape;
	class hkTransform;
	class hkQuaternion;
	class hkVector4;

	class bhkRigidBody : public bhkEntity
	{
	public:
		struct SerializedData
		{
			struct Data30
			{
				uint32_t													collisionFilterInfo;					// 00
				hkpShape*													shape;									// 08
				hkLocalFrame*												localFrame;								// 10
				stl::enumeration<hkpMaterial::ResponseType, std::uint8_t>	responseType;							// 18
				uint16_t													contactPointCallbackDelay;				// 1A
				hkVector4													translation;							// 20
				hkQuaternion												rotation;								// 30
				hkVector4													linearVelocity;							// 40
				hkVector4													angularVelocity;						// 50
				hkMatrix3													inertiaLocal;							// 60
				hkVector4													centerOfMassLocal;						// 90
				float														mass;									// A0
				float														linearDamping;							// A4
				float														angularDamping;							// A8
				int32_t														timeFactor;								// AC
				float														gravityFactor;							// B0
				float														friction;								// B4
				float														rollingFrictionMultiplier;				// B8
				float														restitution;							// BC
				float														maxLinearVelocity;						// C0
				float														maxAngularVelocity;						// C4
				float														allowedPenetrationDepth;				// C8
				stl::enumeration<hkpMotion::MotionType, std::uint8_t>		motionType;								// CC
				bool														isDeactivationIntegrateCounterValid;	// CD
				uint8_t														deactivationClass;						// CE
				int8_t														objectQualityType;						// CF
				int8_t														autoRemoveLevel;						// D0
				uint8_t														unkD1;									// D1
				uint8_t														numShapeKeysInContactPointProperties;	// D2
				bool														isForceCollideOntoPpu;					// D3
			};
			static_assert(sizeof(Data30) == 0xE0);

			uint32_t                            collisionFilterInfo;			// 00
			hkpShape*                           shape;							// 08
			int8_t                              broadphaseHandleType;			// 10
			uint64_t                            unk18;							// 18
			uint64_t                            unk20;							// 20
			uint8_t                             unk28;							// 28
			uint8_t                             unk29;							// 29
			uint16_t                            unk2A;							// 2A
			Data30								unk30;							// 30
		};
		static_assert(sizeof(SerializedData) == 0x110);

		inline static constexpr auto RTTI = RTTI_bhkRigidBody;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkRigidBody;

		~bhkRigidBody() override;  // 00

		// override (bhkEntity)
		const NiRTTI* GetRTTI() const override;                           // 02
		bhkRigidBody* AsBhkRigidBody() override;                          // 15 - { return this; }
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
		void          MoveToWorld(bhkWorld* a_world) override;            // 29
		void          RemoveFromCurrentWorld() override;                  // 2A
		void          Unk_2B(bool) override;                              // 2B
		void          Unk_2C(void) override;                              // 2C - { return 0x110; }
		void          Unk_2D(void) override;                              // 2D
		void          Unk_2E(void) override;                              // 2E
		void*         Unk_2F(bool& out) override;                         // 2F
		void          Unk_30(void) override;                              // 30
		void          Unk_32(void) override;                              // 32

		// add
		virtual void GetPosition(hkVector4& a_outPosition);                                    // 33
		virtual void GetRotation(hkQuaternion& a_outRotation);                                 // 34
		virtual void SetPosition(hkVector4& a_position);                                       // 35
		virtual void SetRotation(hkQuaternion& a_rotation);                                    // 36
		virtual void SetPositionAndRotation(hkVector4& a_position, hkQuaternion& a_rotation);  // 37
		virtual void GetCenterOfMassLocal(hkVector4& a_outCenterOfMassLocal);                  // 38
		virtual void GetCenterOfMassWorld(hkVector4& a_outCenterOfMassWorld);                  // 39
		virtual void GetTransform(hkTransform& a_outTransform);                                // 3A
		virtual void GetAabbWorldspace(hkAabb& a_outAabb);                                     // 3B
		virtual void Unk_3C(void);                                                             // 3C

		// members
		BSTArray<NiPointer<NiRefObject>> constraints;  // 28 - array of smart ptrs to bhkConstraints
	};
	static_assert(sizeof(bhkRigidBody) == 0x40);
}
