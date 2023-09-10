#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IMovementInterface.h"

namespace RE
{
	class MovementMessage;
	class NiPoint3;
	struct PathingPoint;

	class IMovementMessageInterface : public IMovementInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementMessageInterface;

		~IMovementMessageInterface() override;  // 00

		// add
		virtual void EnqueueWarp(const PathingPoint& pathingPoint, const NiPoint3& angle) = 0;        // 01
		virtual void EnqueueMessage(const BSTSmartPointer<MovementMessage>& message) = 0;             // 02
		virtual void ImmediatelyProcessMessage(const BSTSmartPointer<MovementMessage>& message) = 0;  // 03
	};
	static_assert(sizeof(IMovementMessageInterface) == 0x8);
}
