#pragma once

namespace RE
{
	class hkPseudoRandomGenerator
	{
	public:
		uint32_t m_seed;				// 00
		uint32_t m_current;				// 04
	};
	static_assert(sizeof(hkPseudoRandomGenerator) == 0x8);
}
