#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkLocalFrameCollector;
	class hkLocalFrameGroup;
	class hkMemoryAllocator;
	class hkTransform;
	class hkVector4;

	class hkLocalFrame : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkLocalFrame;
		inline static constexpr auto VTABLE = VTABLE_hkLocalFrame;

		~hkLocalFrame() override;  // 00

		virtual void                     GetLocalTransform(hkTransform& transform) const = 0;                                                      // 03
		virtual void                     SetLocalTransform(const hkTransform& transform) = 0;                                                      // 04
		virtual void                     GetLocalPosition(hkVector4& position) const;                                                              // 05
		virtual void                     GetNearbyFrames(const hkVector4& target, float maxDistance, hkLocalFrameCollector& collector) const = 0;  // 06
		virtual const char*              GetName() const = 0;                                                                                      // 07
		virtual const hkLocalFrame*      GetParentFrame() const = 0;                                                                               // 08
		virtual void                     SetParentFrame(const hkLocalFrame* parentFrame) = 0;                                                      // 09
		virtual int                      GetNumChildFrames() const = 0;                                                                            // 0A
		virtual hkLocalFrame*            GetChildFrame(int i) const = 0;                                                                           // 0B
		virtual const hkLocalFrameGroup* GetGroup() const = 0;                                                                                     // 0C
		virtual void                     SetGroup(const hkLocalFrameGroup* localFrameGroup) = 0;                                                   // 0D
		virtual void                     GetDescendants(hkArrayBase<const hkLocalFrame*>& descendants, hkMemoryAllocator& a) const;                // 0E
	};
	static_assert(sizeof(hkLocalFrame) == 0x10);
}
