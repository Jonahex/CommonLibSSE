#pragma once

#include "RE/M/MemoryManager.h"

namespace RE
{
	class BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_BaseFormComponent;

		// add
		virtual ~BaseFormComponent() = default;					// 00
		virtual void InitializeDataComponent() = 0;				// 01
		virtual void ClearDataComponent() = 0;					// 02
		virtual void CopyComponent(BaseFormComponent*)			// 03
		{}

		TES_HEAP_REDEFINE_NEW();
	};
	static_assert(sizeof(BaseFormComponent) == 0x8);
}
