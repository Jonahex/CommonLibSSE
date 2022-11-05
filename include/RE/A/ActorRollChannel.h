#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorRollChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorRollChannel<void, float>) == 0x08);
}
