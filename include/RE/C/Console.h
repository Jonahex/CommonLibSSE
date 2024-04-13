#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	// menuDepth = 12
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kAllowSaving
	// context = kConsole
	class Console : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_Console;
		constexpr static std::string_view MENU_NAME = "Console";

		~Console() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		static NiPointer<TESObjectREFR> GetSelectedRef();
		static ObjectRefHandle          GetSelectedRefHandle();

		void                            SelectReference();

		void SetSelectedRef(NiPointer<TESObjectREFR> a_refPtr);
		void SetSelectedRef(TESObjectREFR* a_ref);
		void SetSelectedRef(ObjectRefHandle a_handle);

		// members
		void* opcode;  // 30
		BSTArray<ObjectRefHandle> raycastedRefHandles;   // 38
#ifdef SKYRIM_SUPPORT_AE
		std::uint8_t  unk4c;                   // 4c
		bool          showAchievementWarning;  // 4d -- only used in ctor
		bool          ctrlKeyHeld;             // 4e
		std::uint8_t  pad4f;                   // 4f
#else
		std::uint64_t selectedRefHandleIndex;  // 50
#endif

	protected:
		void SetSelectedRef_Impl(ObjectRefHandle& a_handle);
	};
#ifdef SKYRIM_SUPPORT_AE
	static_assert(sizeof(Console) == 0x50);
#else
	static_assert(sizeof(Console) == 0x58);
#endif
}
