#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorPitchDeltaChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorPitchDeltaChannel<void, float>) == 0x08);
}
