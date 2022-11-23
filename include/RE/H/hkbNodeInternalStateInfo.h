#pragma once

#include "RE/H/hkbGeneratorSyncInfo.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbNodeInternalStateInfo : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNodeInternalStateInfo;

		~hkbNodeInternalStateInfo() override;  // 00

		hkbGeneratorSyncInfo			m_syncInfo;					// 10
		hkStringPtr						m_name;						// 60
		hkRefPtr<hkReferencedObject>	m_internalState;			// 68
		int16_t							m_nodeId;					// 70
		bool							m_hasActivateBeenCalled;	// 72
	};
	static_assert(sizeof(hkbNodeInternalStateInfo) == 0x78);
}
