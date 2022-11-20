#pragma once

namespace RE
{
	class hkCustomAttributes;

	class hkClassEnum
	{
	public:
		class Item
		{
		public:
			int										m_value;		// 00
			const char*								m_name;			// 08
		};
		static_assert(sizeof(Item) == 0x10);

		enum class FlagValues
		{
			FLAGS_NONE = 0,
		};

		const char*                                 m_name;			// 00
		const Item*									m_items;		// 08
		int                                         m_numItems;		// 10
		hkCustomAttributes*							m_attributes;	// 18
		stl::enumeration<FlagValues, uint32_t>		m_flags;		// 20
	};
	static_assert(sizeof(hkClassEnum) == 0x28);
}
