#include "RE/N/NiQuaternion.h"

#include "RE/N/NiMatrix3.h"

namespace RE
{
	NiQuaternion::NiQuaternion(const NiMatrix3& matrix)
	{
		using func_t = void (*)(NiQuaternion*, const NiMatrix3&);
		REL::Relocation<func_t> func{ RELOCATION_ID(69467, 70844) };
		func(this, matrix);
	}

	NiMatrix3 NiQuaternion::ToMatrix() const
	{
		NiMatrix3 matrix;

		matrix.entry[0][0] = 1 - 2 * (z * z + y * y);
		matrix.entry[0][1] = 2 * (x * y - w * z);
		matrix.entry[0][2] = 2 * (x * z + w * y);
		matrix.entry[1][0] = 2 * (x * y + w * z);
		matrix.entry[1][1] = 1 - 2 * (z * z + x * x);
		matrix.entry[1][2] = 2 * (y * z - w * x);
		matrix.entry[2][0] = 2 * (x * z - w * y);
		matrix.entry[2][1] = 2 * (y * z + w * x);
		matrix.entry[2][2] = 1 - 2 * (y * y + x * x);

		return matrix;
	}

	NiQuaternion NiQuaternion::operator+(const NiQuaternion& that) const
	{
		return NiQuaternion(w + that.w, x + that.x, y + that.y, z + that.z);
	}

	NiQuaternion NiQuaternion::operator*(const NiQuaternion& that) const
	{
		return NiQuaternion(w * that.w - x * that.x - y * that.y - z * that.z, 
			w * that.x + x * that.w + y * that.z - z * that.y,
			w * that.y - x * that.z + y * that.w + z * that.x,
			w * that.z + x * that.y - y * that.x + z * that.w);
	}

	NiQuaternion NiQuaternion::operator*(float mul) const
	{
		return NiQuaternion(w * mul, x * mul, y * mul, z * mul);
	}

	NiQuaternion& NiQuaternion::Normalize()
	{
		const float invNorm = 1 / std::sqrt(w * w + x * x + y * y + z * z);
		w = w * invNorm;
		x = x * invNorm;
		y = y * invNorm;
		z = z * invNorm;

		return *this;
	}

	NiQuaternion NiQuaternion::Inverse()
	{
		return NiQuaternion(w, -x, -y, -z).Normalize();
	}

	NiQuaternion operator*(float mul, const NiQuaternion& quat)
	{
		return quat * mul;
	}
}
