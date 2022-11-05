#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorLookAtChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorLookAtChannel<void, float>) == 0x08);
}
