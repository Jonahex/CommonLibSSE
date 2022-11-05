#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorSpeedChannel
	{
	public:
		using ValueType = Val;

		// members
		std::uint32_t unk00;    // 00
		Val           unk04;	// 04
		T*            type;		// ??
	};
	static_assert(sizeof(ActorSpeedChannel<void, float>) == 0x10);
}
