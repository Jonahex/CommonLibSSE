#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorDirectionChannel
	{
	public:
		using ValueType = Val;

		// members
		uint64_t unk00;  // 00
		T*       type;   // ??
	};
	static_assert(sizeof(ActorDirectionChannel<void, float>) == 0x10);
}
