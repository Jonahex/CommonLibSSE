#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorSpeedChannel
	{
	public:
		using ValueType = Val;

		// members
		std::uint32_t actualSpeed;  // 00
		Val           actorHeight;  // 04
		T*            type;         // ??
	};
	static_assert(sizeof(ActorSpeedChannel<void, float>) == 0x10);
}
