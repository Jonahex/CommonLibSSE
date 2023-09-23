#pragma once

#include "RE/I/IMovementInterface.h"

namespace RE
{
	class IMovementPlayIdleResult;
	class ISelectIdleFilter;

	struct IdleAnimationData;
	struct PathingParameters;
	struct Tweener;

	class IMovementSelectIdle : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementSelectIdle;

		~IMovementSelectIdle() override;  // 00

		// add
		virtual bool SelectIdle(const PathingParameters& pathingParameters, ISelectIdleFilter* selectIdleFilter, IdleAnimationData& outIdleData) = 0;  // 01
		virtual bool EstimateRotationVelocityInIdle(const IdleAnimationData& idleData, NiPoint3& outRotationVelocity) const = 0;                       // 02
		virtual void PlayIdle(const BSFixedString& eventName, const Tweener& tweener, IMovementPlayIdleResult*& playIdleResult) = 0;                   // 03
		virtual void ClearIdles() = 0;                                                                                                                 // 04
		virtual bool HasIdleToPlay() const = 0;                                                                                                        // 05
	};
	static_assert(sizeof(IMovementSelectIdle) == 0x8);
}
