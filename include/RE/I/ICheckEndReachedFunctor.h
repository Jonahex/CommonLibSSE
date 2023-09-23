#pragma once

#include "RE/I/IPathFollowerState.h"

namespace RE
{
	class ICheckEndReachedFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_ICheckEndReachedFunctor;

		virtual ~ICheckEndReachedFunctor();  // 00

		// add
		virtual bool     Check(const IPathFollowerState::Context& context) = 0;  // 01
		virtual void     OnSaveGame(BSPathingStreamWrite& stream) const;         // 02
		virtual uint32_t OnLoadGame(BSPathingStreamRead& stream);                // 03
	};
	static_assert(sizeof(ICheckEndReachedFunctor) == 0x8);
}
