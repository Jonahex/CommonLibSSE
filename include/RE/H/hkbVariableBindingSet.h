#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkClass;

	class hkbVariableBindingSet : public hkReferencedObject
	{
	public:
		struct Binding
		{
			enum class BindingType
			{
				BINDING_TYPE_VARIABLE = 0,
				BINDING_TYPE_CHARACTER_PROPERTY = 1,
			};

			enum class InternalBindingFlags
			{
				FLAG_NONE = 0,
				FLAG_OUTPUT = 1,
			};

			// Properties
			hkStringPtr										m_memberPath;             // 00
			const hkClass*									m_memberClass;            // 08
			int32_t											m_offsetInObjectPlusOne;  // 10
			int32_t											m_offsetInArrayPlusOne;   // 14
			int32_t											m_rootVariableIndex;      // 18
			int32_t											m_variableIndex;          // 1C
			int8_t											m_bitIndex;               // 20
			stl::enumeration<BindingType, int8_t>			m_bindingType;            // 21
			uint8_t											m_memberType;             // 22
			int8_t											m_variableType;           // 23
			stl::enumeration<InternalBindingFlags, int8_t>	m_flags;                  // 24
		};
		static_assert(sizeof(Binding) == 0x28);

		inline static constexpr auto RTTI = RTTI_hkbVariableBindingSet;

		~hkbVariableBindingSet() override;									// 00

		// Properties
		hkArray<Binding>						m_bindings;					// 10
		int32_t									m_indexOfBindingToEnable;	// 20
		bool									m_hasOutputBinding;			// 24
	};
	static_assert(sizeof(hkbVariableBindingSet) == 0x28);
}
