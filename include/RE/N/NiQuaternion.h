#pragma once

namespace RE
{
	class NiMatrix3;

	class NiQuaternion
	{
	public:
		constexpr NiQuaternion() = default;
		constexpr NiQuaternion(float inW, float inX, float inY, float inZ) :
			w(inW), x(inX), y(inY), z(inZ) 
		{}
		NiQuaternion(const NiMatrix3& matrix);

		NiMatrix3     ToMatrix() const;
		NiQuaternion& Normalize();
		NiQuaternion Inverse();

		NiQuaternion operator+(const NiQuaternion& that) const;
		NiQuaternion operator*(const NiQuaternion& that) const;
		NiQuaternion operator*(float mul) const;

		// members
		float w = 1.f;  // 00
		float x = 0.f;  // 04
		float y = 0.f;  // 08
		float z = 0.f;  // 0C
	};
	static_assert(sizeof(NiQuaternion) == 0x10);

	NiQuaternion operator*(float mul, const NiQuaternion& quat);
}
