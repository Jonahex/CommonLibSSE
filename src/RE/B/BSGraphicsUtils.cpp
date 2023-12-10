#include "RE/B/BSGraphicsUtils.h"

namespace RE::BSGraphics::Utils
{
	::DirectX::XMMATRIX ConvertTransform(const NiTransform& source)
	{
		::DirectX::XMMATRIX result;

		result.r[0] = ::DirectX::XMVectorScale(::DirectX::XMVectorSet(
												   source.rotate.entry[0][0],
												   source.rotate.entry[1][0],
												   source.rotate.entry[2][0],
												   0.0f),
			source.scale);

		result.r[1] = ::DirectX::XMVectorScale(::DirectX::XMVectorSet(
												   source.rotate.entry[0][1],
												   source.rotate.entry[1][1],
												   source.rotate.entry[2][1],
												   0.0f),
			source.scale);

		result.r[2] = ::DirectX::XMVectorScale(::DirectX::XMVectorSet(
												   source.rotate.entry[0][2],
												   source.rotate.entry[1][2],
												   source.rotate.entry[2][2],
												   0.0f),
			source.scale);

		result.r[3] = ::DirectX::XMVectorSet(
			source.translate.x,
			source.translate.y,
			source.translate.z,
			1.0f);

		return result;
	}

	::DirectX::XMVECTOR ConvertColorA(const NiColorA& source)
	{
		return _mm_load_ps(&source.red);
	}
}
