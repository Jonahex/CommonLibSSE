#pragma once

namespace RE
{
	class hkbRoleAttribute
	{
	public:
		enum class Role
		{
			ROLE_DEFAULT = 0,
			ROLE_FILE_NAME = 1,
			ROLE_BONE_INDEX = 2,
			ROLE_BONE_INDEX_MAP = 3,
			ROLE_EVENT_ID = 4,
			ROLE_VARIABLE_INDEX = 5,
			ROLE_ATTRIBUTE_INDEX = 6,
			ROLE_TIME = 7,
		};

		enum class RoleFlags
		{
			FLAG_NONE = 0,
			FLAG_RAGDOLL = 1,
			FLAG_NORMALIZED = 2,
			FLAG_NOT_VARIABLE = 4,
			FLAG_HIDDEN = 8,
			FLAG_OUTPUT = 16,
			FLAG_NOT_CHARACTER_PROPERTY = 32,
		};

		// Properties
		stl::enumeration<Role, int16_t>      m_role;
		stl::enumeration<RoleFlags, int16_t> m_flags;
	};
	static_assert(sizeof(hkbRoleAttribute) == 0x04);
}
