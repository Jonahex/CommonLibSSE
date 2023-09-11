#pragma once

namespace RE
{
	class IPathFollowerAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathFollowerAction;

		virtual ~IPathFollowerAction();  // 00

		// add
		virtual void Unk01(void);      // 01
		virtual void Unk02(void) = 0;  // 02
		virtual void Unk03(void) = 0;  // 03
	};
	static_assert(sizeof(IPathFollowerAction) == 0x8);
}
