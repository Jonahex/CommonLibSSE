#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	struct PathingPoint;

	class BSPathingDoor :
		public BSIntrusiveRefCounted  // 000
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPathingDoor;

		virtual ~BSPathingDoor();  // 00

		// add
		virtual uint32_t GetNameHash() = 0;                                                     // 01
		virtual uint32_t GetDoorFormId() = 0;                                                   // 02
		virtual void     OnSaveGame(BSPathingStreamWrite* stream) = 0;                          // 03
		virtual void     OnLoadGame(BSPathingStreamRead* stream) = 0;                           // 04
		virtual void     Unk05(void*) = 0;                                                      // 05 - called only in MovementMessageActivateDoor::Unk04
		virtual bool     IsDoorOpen() = 0;                                                      // 06
		virtual bool     IsDoorClosed() = 0;                                                    // 07
		virtual bool     IsDoorOpening() = 0;                                                   // 08
		virtual bool     IsDoorClosing() = 0;                                                   // 09
		virtual bool     GetOriginPoint(PathingPoint& originPoint) = 0;                         // 0A
		virtual bool     GetDestinationPoint(PathingPoint& destinationPoint) = 0;               // 0B
		virtual bool     GetLinkedDoorRotation(float& rotation) = 0;                            // 0C
		virtual bool     GetDoorRotation(float& rotation) = 0;                                  // 0D
		virtual float    GetActorFadeDistance() = 0;                                            // 0E
		virtual bool     GetLinkedPathingDoor(const BSTSmartPointer<BSPathingDoor>& that) = 0;  // 0F
		virtual bool     Equals(const BSTSmartPointer<BSPathingDoor>& that) = 0;                // 10
		virtual void     LogDoorForm(const char* buffer, int32_t bufferSize) = 0;               // 11
	};
	static_assert(sizeof(BSPathingDoor) == 0x10);
}
