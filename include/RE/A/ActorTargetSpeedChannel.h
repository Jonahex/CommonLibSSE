#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorTargetSpeedChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorTargetSpeedChannel<void, float>) == 0x08);
}
