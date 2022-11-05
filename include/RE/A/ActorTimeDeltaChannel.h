#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorTimeDeltaChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorTimeDeltaChannel<void, float>) == 0x08);
}
