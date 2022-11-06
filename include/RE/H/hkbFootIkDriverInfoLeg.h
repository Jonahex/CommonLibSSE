#pragma once

#include "RE/H/hkQuaternion.h"

namespace RE
{
	class hkbFootIkDriverInfoLeg
	{
	public:
		hkQuaternion m_prevAnkleRotLS;				// 00
		hkVector4    m_kneeAxisLS;					// 10
		hkVector4    m_footEndLS;					// 20
		float        m_footPlantedAnkleHeightMS;	// 30
		float        m_footRaisedAnkleHeightMS;		// 34
		float        m_maxAnkleHeightMS;			// 38
		float        m_minAnkleHeightMS;			// 3C
		float        m_maxKneeAngleDegrees;			// 40
		float        m_minKneeAngleDegrees;			// 44
		float        m_maxAnkleAngleDegrees;		// 48
		std::int16_t m_hipIndex;					// 4C
		std::int16_t m_kneeIndex;					// 4E
		std::int16_t m_ankleIndex;					// 50
	};
	static_assert(sizeof(hkbFootIkDriverInfoLeg) == 0x60);
}
