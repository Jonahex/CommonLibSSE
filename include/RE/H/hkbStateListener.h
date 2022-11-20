#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbContext;
	class hkbStateMachine;

	class hkbStateListener : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStateListener;

		~hkbStateListener() override;																			// 00

		// add
		virtual void onEnterImplementation(const hkbContext& context, hkbStateMachine& sm) {}					// 03
		virtual void onUpdateImplementation(const hkbContext& context, float timestep, hkbStateMachine& sm) {}	// 04
		virtual void onExitImplementation(const hkbContext& context, hkbStateMachine& sm) {}					// 05
		virtual hkbStateListener* clone() { return nullptr; }													// 06
	};
}
