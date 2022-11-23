#pragma once

#include "RE/H/hkbBehaviorGraphStringData.h"

namespace RE
{
	class hkbEventInfo;
	class hkbVariableBounds;
	class hkbVariableInfo;
	class hkbVariableValueSet;

	union hkbVariableValue;

	class hkbBehaviorGraphData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraphData;

		virtual ~hkbBehaviorGraphData() = default;  // 00

		// members
		hkArray<float>                       attributeDefaults;			// 10
		hkArray<hkbVariableInfo>             variableInfos;				// 20
		hkArray<hkbVariableInfo>             characterPropertyInfos;	// 30
		hkArray<hkbVariableInfo>             eventInfos;				// 40
		hkArray<hkbVariableValue>            wordMinVariableValues;		// 50
		hkArray<hkbVariableValue>            wordMaxVariableValues;		// 60
		hkbVariableValueSet*                 variableInitialValues;		// 70
		hkRefPtr<hkbBehaviorGraphStringData> stringData;				// 78
	};
	static_assert(sizeof(hkbBehaviorGraphData) == 0x80);
}
