#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class IMovementInterface;

	class IMovementControllerRegisterInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IMovementControllerRegisterInterface;

		virtual ~IMovementControllerRegisterInterface();  // 00

		// add
		virtual void                      AddInterface(const BSFixedString& name, IMovementInterface* interface) = 0;  // 01
		virtual const IMovementInterface* GetInterface(const BSFixedString& name) const = 0;                           // 02
		virtual IMovementInterface*       GetInterface(const BSFixedString& name) = 0;                                 // 03
		virtual void                      DeleteInterface(const BSFixedString& name) = 0;                              // 04
	};
	static_assert(sizeof(IMovementControllerRegisterInterface) == 0x8);
}
