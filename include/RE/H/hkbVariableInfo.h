#pragma once

#include "RE/H/hkbRoleAttribute.h"

namespace RE
{
	class hkbVariableInfo
	{
	public:
		enum class VariableType
		{
			VARIABLE_TYPE_INVALID = -1,
			VARIABLE_TYPE_BOOL = 0,
			VARIABLE_TYPE_INT8 = 1,
			VARIABLE_TYPE_INT16 = 2,
			VARIABLE_TYPE_INT32 = 3,
			VARIABLE_TYPE_REAL = 4,
			VARIABLE_TYPE_POINTER = 5,
			VARIABLE_TYPE_VECTOR3 = 6,
			VARIABLE_TYPE_VECTOR4 = 7,
			VARIABLE_TYPE_QUATERNION = 8,
		};

		// Properties
		hkbRoleAttribute                       m_role;
		stl::enumeration<VariableType, int8_t> m_type;
	};
	static_assert(sizeof(hkbVariableInfo) == 0x6);
}
