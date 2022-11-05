#pragma once

namespace RE
{
	template <class T, class Val>
	class ActorWeaponSpeedChannel
	{
	public:
		using ValueType = Val;

		// members
		T*       type;   // ??
	};
	static_assert(sizeof(ActorWeaponSpeedChannel<void, float>) == 0x08);
}
