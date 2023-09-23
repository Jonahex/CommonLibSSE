#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorSpeedChannel
	{
	public:
		using ValueType = Val;

		// members
		Val           graphSpeed;   // 00
		Val           actorHeight;  // 04
		T*            type;         // ??
	};
	static_assert(sizeof(ActorSpeedChannel<void, float>) == 0x10);
}
