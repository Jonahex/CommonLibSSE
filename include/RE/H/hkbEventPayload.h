#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
	class hkbEventPayload : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventPayload;

		~hkbEventPayload() override;		// 00
	};
	static_assert(sizeof(hkbEventPayload) == 0x10);

	class hkbRealEventPayload : public hkbEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbRealEventPayload;

		~hkbRealEventPayload() override;	// 00

		float m_data;						// 10
	};
	static_assert(sizeof(hkbRealEventPayload) == 0x18);

	class hkbIntEventPayload : public hkbEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbIntEventPayload;

		~hkbIntEventPayload() override;		// 00

		int32_t m_data;						// 10
	};
	static_assert(sizeof(hkbIntEventPayload) == 0x18);

	class hkbStringEventPayload : public hkbEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbStringEventPayload;

		~hkbStringEventPayload() override;  // 00

		hkStringPtr m_data;					// 10
	};
	static_assert(sizeof(hkbStringEventPayload) == 0x18);

	class hkbNamedEventPayload : public hkbEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNamedEventPayload;

		~hkbNamedEventPayload() override;	// 00

		hkStringPtr m_name;					// 10
	};
	static_assert(sizeof(hkbNamedEventPayload) == 0x18);

	class hkbNamedRealEventPayload : public hkbNamedEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNamedRealEventPayload;

		~hkbNamedRealEventPayload() override;	// 00

		float m_data;							// 18
	};
	static_assert(sizeof(hkbNamedRealEventPayload) == 0x20);

	class hkbNamedIntEventPayload : public hkbNamedEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNamedIntEventPayload;

		~hkbNamedIntEventPayload() override;	// 00

		int32_t m_data;							// 18
	};
	static_assert(sizeof(hkbNamedIntEventPayload) == 0x20);

	class hkbNamedStringEventPayload : public hkbNamedEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbNamedStringEventPayload;

		~hkbNamedStringEventPayload() override; // 00

		hkStringPtr m_data;						// 18
	};
	static_assert(sizeof(hkbNamedStringEventPayload) == 0x20);

	class hkbEventPayloadList : public hkbEventPayload
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbEventPayloadList;

		~hkbEventPayloadList() override;		// 00

	public:
		hkArray<hkbEventPayload*> m_payloads;	// 10
	};
	static_assert(sizeof(hkbEventPayloadList) == 0x20);
}
