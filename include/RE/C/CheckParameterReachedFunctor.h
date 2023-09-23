#pragma once

#include "RE/I/ICheckEndReachedFunctor.h"

namespace RE
{
	class CheckParameterReachedFunctor : public ICheckEndReachedFunctor
	{
	public:
		inline static constexpr auto RTTI = RTTI_CheckParameterReachedFunctor;

		~CheckParameterReachedFunctor() override;  // 00

		// override (ICheckEndReachedFunctor)
		bool     Check(const IPathFollowerState::Context& context) override;  // 01
		void     OnSaveGame(BSPathingStreamWrite& stream) const override;     // 02
		uint32_t OnLoadGame(BSPathingStreamRead& stream) override;            // 03

		float targetParameter;  // 08
	};
	static_assert(sizeof(CheckParameterReachedFunctor) == 0x10);
}
