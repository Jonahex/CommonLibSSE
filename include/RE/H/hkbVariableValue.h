#pragma once

namespace RE
{
	union hkbVariableValue
	{
		bool         b;
		std::int32_t i;
		float        f;
	};
	static_assert(sizeof(hkbVariableValue) == 0x4);
}
