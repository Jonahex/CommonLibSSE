#pragma once

namespace RE
{
	class hkClass;
	class hkClassEnum;
	class hkClassMember;
	class hkCustomAttributes;

	class hkClass
	{
	public:
		enum class SignatureFlags
		{
			SIGNATURE_LOCAL = 1
		};

		enum class FlagValues
		{
			FLAGS_NONE = 0,
			FLAGS_NOT_SERIALIZABLE = 1
		};

		const char*                                 m_name;						// 00
		const hkClass*                              m_parent;					// 08
		int                                         m_objectSize;				// 10
		int                                         m_numImplementedInterfaces;	// 14
		const hkClassEnum*							m_declaredEnums;			// 18
		int                                         m_numDeclaredEnums;			// 20
		const hkClassMember*						m_declaredMembers;			// 28
		int                                         m_numDeclaredMembers;		// 30
		const void*                                 m_defaults;					// 38
		const hkCustomAttributes*                   m_attributes;				// 40
		stl::enumeration<FlagValues, std::uint32_t> m_flags;					// 48
		int                                         m_describedVersion;			// 4C
	};
	static_assert(sizeof(hkClass) == 0x50);
}
