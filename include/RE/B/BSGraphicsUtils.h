#pragma once

#include "RE/N/NiColor.h"
#include "RE/N/NiTransform.h"

#include "DirectXMath.h"

namespace RE::BSGraphics::Utils
{
	::DirectX::XMMATRIX ConvertTransform(const NiTransform& source);
	::DirectX::XMVECTOR ConvertColorA(const NiColorA& source);
}
