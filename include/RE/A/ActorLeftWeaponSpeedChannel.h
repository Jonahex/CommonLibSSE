#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorLeftWeaponSpeedChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorLeftWeaponSpeedChannel<void, float>) == 0x08);
}
