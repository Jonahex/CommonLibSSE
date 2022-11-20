#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbBindableCollector;
	class hkbVariableBindingSet;

	class hkbBindable : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBindable;

		~hkbBindable() override;											// 00

		// add
		virtual void CollectBindables(hkbBindableCollector& collector);		// 03

		// members
		hkRefPtr<hkbVariableBindingSet> variableBindingSet;  // 10
		hkArray<hkbBindable*>           cachedBindables;     // 18
		bool                            areBindablesCached;  // 28
	};
	static_assert(sizeof(hkbBindable) == 0x30);
}
