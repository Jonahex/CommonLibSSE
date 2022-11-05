#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorWantBlockChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorWantBlockChannel<void, float>) == 0x08);
}
