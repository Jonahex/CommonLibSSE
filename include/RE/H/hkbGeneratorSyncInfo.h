#pragma once

namespace RE
{
	class hkbGeneratorSyncInfo
	{
	public:
		struct SyncPoint
		{
			int		m_id;		// 00
			float	m_time;		// 04
		};
		static_assert(sizeof(SyncPoint) == 0x08);

		SyncPoint						m_syncPoints[8];	// 00
		float							m_baseFrequency;	// 40
		float							m_localTime;		// 44
		float							m_playbackSpeed;	// 48
		int8_t							m_numSyncPoints;	// 4C
		bool							m_isCyclic;			// 4D
		bool							m_isMirrored;		// 4E
		bool							m_isAdditive;		// 4F
	};
	static_assert(sizeof(hkbGeneratorSyncInfo) == 0x50);
}
