#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkbVariableValue.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkbVariableValueSet : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbVariableValueSet;

		// override (hkReferencedObject)
		~hkbVariableValueSet() override;  // 00

		hkArray<hkbVariableValue>    m_wordVariableValues;		// 10
		hkArray<hkVector4>           m_quadVariableValues;		// 20
		hkArray<hkReferencedObject*> m_variantVariableValues;	// 30
	};
	static_assert(sizeof(hkbVariableValueSet) == 0x40);
}
