#pragma once

#include "RE/B/BSCoreTypes.h"
#include "RE/B/BSPathingDoor.h"
#include "RE/P/PathingPoint.h"

namespace RE
{
	class PathingDoor : public BSPathingDoor
	{
	public:
		inline static constexpr auto RTTI = RTTI_PathingDoor;

		~PathingDoor() override;  // 00

		// override (BSPathingDoor)
		uint32_t GetNameHash() override;                                                     // 01
		uint32_t GetDoorFormId() override;                                                   // 02
		void     OnSaveGame(BSPathingStreamWrite* stream) override;                          // 03
		void     OnLoadGame(BSPathingStreamRead* stream) override;                           // 04
		void     Unk05(void*) override;                                                      // 05 - called only in MovementMessageActivateDoor::Unk04
		bool     IsDoorOpen() override;                                                      // 06
		bool     IsDoorClosed() override;                                                    // 07
		bool     IsDoorOpening() override;                                                   // 08
		bool     IsDoorClosing() override;                                                   // 09
		bool     GetOriginPoint(PathingPoint& originPoint) override;                         // 0A
		bool     GetDestinationPoint(PathingPoint& destinationPoint) override;               // 0B
		bool     GetLinkedDoorRotation(float& rotation) override;                            // 0C
		bool     GetDoorRotation(float& rotation) override;                                  // 0D
		float    GetActorFadeDistance() override;                                            // 0E
		bool     GetLinkedPathingDoor(const BSTSmartPointer<BSPathingDoor>& that) override;  // 0F
		bool     Equals(const BSTSmartPointer<BSPathingDoor>& that) override;                // 10
		void     LogDoorForm(const char* buffer, int32_t bufferSize) override;               // 11

		// members
		uint32_t     doorFormID;        // 10
		RefHandle    doorHandle;        // 14
		PathingPoint originPoint;       // 18
		PathingPoint destinationPoint;  // 48
	};
	static_assert(sizeof(PathingDoor) == 0x78);
}
