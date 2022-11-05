#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorWardHealthChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorWardHealthChannel<void, float>) == 0x08);
}
