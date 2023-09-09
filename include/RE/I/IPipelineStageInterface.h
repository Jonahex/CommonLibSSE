#pragma once

namespace RE
{
	class IPipelineStageInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPipelineStageInterface;

		virtual ~IPipelineStageInterface();  // 00
	};
	static_assert(sizeof(IPipelineStageInterface) == 0x8);
}
