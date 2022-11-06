#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkaRaycastInterface;
	class hkaSkeleton;

	class hkaFootPlacementIkSolver : public hkReferencedObject
	{
	public:
		struct Setup
		{
			const hkaSkeleton* m_skeleton;					// 00
			std::int16_t       m_hipIndex;					// 08
			std::int16_t       m_kneeIndex;					// 0A
			std::int16_t       m_ankleIndex;				// 0C
			hkVector4          m_kneeAxisLS;				// 10
			hkVector4          m_footEndLS;					// 20
			hkVector4          m_worldUpDirectionWS;		// 30
			hkVector4          m_modelUpDirectionMS;		// 40
			float              m_originalGroundHeightMS;	// 50
			float              m_footPlantedAnkleHeightMS;	// 54
			float              m_footRaisedAnkleHeightMS;	// 58
			float              m_maxAnkleHeightMS;			// 5C
			float              m_minAnkleHeightMS;			// 60
			float              m_cosineMaxKneeAngle;		// 64
			float              m_cosineMinKneeAngle;		// 68
			float              m_raycastDistanceUp;			// 6C
			float              m_raycastDistanceDown;		// 70
			bool               m_useFootLocking;			// 74
		};
		static_assert(sizeof(Setup) == 0x80);

		struct Input
		{
			hkQsTransform			m_originalAnkleTransformMS;	// 00
			hkQsTransform			m_worldFromModel;			// 30
			bool					m_footPlacementOn;			// 60
			hkaRaycastInterface*	_raycastInterface;			// 68
			float					m_onOffGain;				// 70
			float					m_groundAscendingGain;		// 74
			float					m_groundDescendingGain;		// 78
			float					m_footPlantedGain;			// 7C
			float					m_footRaisedGain;			// 80
			float					m_footUnlockGain;			// 84
			std::uint32_t			m_collisionFilterInfo;		// 88
			bool					m_useCollisionFilterInfo;	// 8C
		};
		static_assert(sizeof(Setup) == 0x90);

		struct Output
		{
			float m_verticalError;	// 00
			bool  m_hitSomething;	// 04
		};
		static_assert(sizeof(Output) == 0x08);

		Setup		m_setup;						// 00
		float		m_currentWeight;				// 70
		float		m_previousGroundHeightWS;		// 74
		hkVector4	m_previousGroundNormalWS;		// 80
		bool		m_previousVerticalDisplacement;	// 90
		bool		m_isFootLocked;					// 91
		hkVector4	m_lockedFootPositionInWS;		// A0
		hkVector4	m_lockedFootEndPositionInWS;	// B0
		hkVector4	m_footUnlockingOffset;			// C0
	};
	static_assert(sizeof(hkaFootPlacementIkSolver) == 0xD0);
}
