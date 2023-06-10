#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorTurnDeltaChannel
	{
	public:
		using ValueType = Val;

		// members
		float actualRotationSpeed;  // 00
		T*    type;                 // ??
	};
	static_assert(sizeof(ActorTurnDeltaChannel<void, float>) == 0x10);
}
