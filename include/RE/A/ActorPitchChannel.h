#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorPitchChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorPitchChannel<void, float>) == 0x08);
}
