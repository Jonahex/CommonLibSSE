#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/P/PlayerInputHandler.h"
#include "RE/T/TESCameraState.h"

namespace RE
{
	class FreeCameraState :
		public TESCameraState,     // 00
		public PlayerInputHandler  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_FreeCameraState;
		inline static constexpr auto VTABLE = VTABLE_FreeCameraState;

		~FreeCameraState() override;  // 00

		// override (TESCameraState)
		void Begin() override;                                               // 01
		void End() override;                                                 // 02
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04
		void GetTranslation(NiPoint3& a_translation) override;               // 05

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                          // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_movementData) override;  // 04

		// members
		NiPoint3 position;				// 30
		float    eulerX;				// 3C
		float    eulerZ;				// 40
		float    zUp;					// 44
		float    zDown;					// 48
		int16_t  verticalDirection;		// 4C
		bool     isFast;				// 4E
		bool     lockToZPlane;			// 4F
	};
	static_assert(sizeof(FreeCameraState) == 0x50);
}
