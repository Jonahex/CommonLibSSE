#pragma once

namespace RE
{
	class hkClass;

	struct hkVariant
	{
		void*          m_object;	// 00
		const hkClass* m_class;		// 08
	};
	static_assert(sizeof(hkVariant) == 0x10);
}
