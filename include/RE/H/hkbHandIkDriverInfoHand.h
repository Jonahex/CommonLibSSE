#pragma once

#include "RE/H/hkQuaternion.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbHandIkDriverInfoHand
	{
	public:
		hkVector4		m_elbowAxisLS;				// 00
		hkVector4		m_backHandNormalLS;			// 10
		hkVector4		m_handOffsetLS;				// 20
		hkQuaternion	m_handOrienationOffsetLS;	// 30
		float			m_maxElbowAngleDegrees;		// 40
		float			m_minElbowAngleDegrees;		// 44
		std::int16_t    m_shoulderIndex;			// 48
		std::int16_t	m_shoulderSiblingIndex;		// 4A
		std::int16_t    m_elbowIndex;				// 4C
		std::int16_t    m_elbowSiblingIndex;		// 4E
		std::int16_t    m_wristIndex;				// 50
		bool			m_enforceEndPosition;		// 52
		bool			m_enforceEndRotation;		// 53
		hkStringPtr		m_localFrameName;			// 58
	};
	static_assert(sizeof(hkbHandIkDriverInfoHand) == 0x60);
}
