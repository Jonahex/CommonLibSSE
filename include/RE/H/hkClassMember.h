#pragma once

namespace RE
{
	class hkClass;
	class hkClassEnum;
	class hkCustomAttributes;

	class hkClassMember
	{
	public:
		enum class Type
		{
			TYPE_VOID = 0,
			TYPE_BOOL,
			TYPE_CHAR,
			TYPE_INT8,
			TYPE_UINT8,
			TYPE_INT16,
			TYPE_UINT16,
			TYPE_INT32,
			TYPE_UINT32,
			TYPE_INT64,
			TYPE_UINT64,
			TYPE_REAL,
			TYPE_VECTOR4,
			TYPE_QUATERNION,
			TYPE_MATRIX3,
			TYPE_ROTATION,
			TYPE_QSTRANSFORM,
			TYPE_MATRIX4,
			TYPE_TRANSFORM,
			TYPE_ZERO,
			TYPE_POINTER,
			TYPE_FUNCTIONPOINTER,
			TYPE_ARRAY,
			TYPE_INPLACEARRAY,
			TYPE_ENUM,
			TYPE_STRUCT,
			TYPE_SIMPLEARRAY,
			TYPE_HOMOGENEOUSARRAY,
			TYPE_VARIANT,
			TYPE_CSTRING,
			TYPE_ULONG,
			TYPE_FLAGS,
			TYPE_HALF,
			TYPE_STRINGPTR,
			TYPE_RELARRAY,
			TYPE_MAX
		};

		enum class FlagValues
		{
			FLAGS_NONE = 0,
			ALIGN_8 = 128,
			ALIGN_16 = 256,
			NOT_OWNED = 512,
			SERIALIZE_IGNORED = 1024,
			ALIGN_32 = 2048,
			ALIGN_REAL = ALIGN_16
		};

		const char*                                 m_name;			// 00
		const hkClass*                              m_class;		// 08
		const hkClassEnum*                          m_enum;			// 10
		stl::enumeration<Type, std::uint8_t>        m_type;			// 18
		stl::enumeration<Type, std::uint8_t>        m_subtype;		// 19
		std::int16_t                                m_cArraySize;	// 1A
		stl::enumeration<FlagValues, std::uint16_t> m_flags;		// 1C
		std::uint16_t                               m_offset;		// 1E
		const hkCustomAttributes*                   m_attributes;	// 20
	};
	static_assert(sizeof(hkClassMember) == 0x28);
}
