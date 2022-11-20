#pragma once

#include "RE/H/hkVariant.h"

namespace RE
{
	class hkCustomAttributes
	{
	public:
		struct Attribute
		{
			const char*			m_name;				// 00
			hkVariant			m_value;			// 08
		};
		static_assert(sizeof(Attribute) == 0x18);

		const Attribute*		m_attributes;		// 00
		int                     m_numAttributes;	// 08
	};
	static_assert(sizeof(hkCustomAttributes) == 0x10);
}
