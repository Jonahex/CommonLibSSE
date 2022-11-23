#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	class hkbGenerator : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbGenerator;

		~hkbGenerator() override;  // 00

		// override (hkbNode)
		bool IsGenerator() const override;  // 15 - { return 1; }

		// add
		virtual void Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output) = 0;	// 17
		virtual bool CanRecycleOutput();																										// 18 - { return 0; }
		virtual void UpdateSync(const hkbContext& a_context);																					// 19
		virtual void StartEcho(float echoDuration);																								// 1A - { return; }
		virtual void PreUpdate(const hkbContext& context, float timestep);																		// 1B - { return; }
	};
	static_assert(sizeof(hkbGenerator) == 0x48);
}
