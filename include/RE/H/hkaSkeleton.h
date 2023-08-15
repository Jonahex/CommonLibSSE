#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkaBone;
	class hkLocalFrame;
	class hkQsTransform;

	class hkaSkeleton : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkaSkeleton;
		inline static constexpr auto VTABLE = VTABLE_hkaSkeleton;

		struct LocalFrameOnBone
		{
			hkRefPtr<hkLocalFrame> localFrame;  // 00
			std::int16_t           boneIndex;   // 08
		};
		static_assert(sizeof(LocalFrameOnBone) == 0x10);

		~hkaSkeleton() override;  // 00

		// members
		hkStringPtr               name;             // 10
		hkArray<std::int16_t>     parentIndices;    // 18
		hkArray<hkaBone>          bones;            // 28
		hkArray<hkQsTransform>    referencePose;    // 38
		hkArray<float>            referenceFloats;  // 48
		hkArray<hkStringPtr>      floatSlots;       // 58
		hkArray<LocalFrameOnBone> localFrames;      // 68
	};
	static_assert(sizeof(hkaSkeleton) == 0x78);
}
