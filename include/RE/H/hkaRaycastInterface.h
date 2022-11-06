#pragma once

#include "RE/H/hkVector4.h"
#include "RE/Offsets_RTTI.h"

namespace RE
{
	class hkaRaycastInterface
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkaRaycastInterface;

		virtual ~hkaRaycastInterface();																															// 00
		virtual bool castRay(const hkVector4& fromWS, const hkVector4& toWS, float& hitFractionOut, hkVector4& normalWSOut);									// 01
		virtual bool castRay(const hkVector4& fromWS, const hkVector4& toWS, std::uint32_t collisionFilterInfo, float& hitFractionOut, hkVector4& normalWSOut);	// 02
	};
	static_assert(sizeof(hkaRaycastInterface) == 0x8);
}
