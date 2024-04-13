#include "RE/N/NiAlphaProperty.h"

namespace RE
{
	bool NiAlphaProperty::GetAlphaBlending() const
	{
		return alphaFlags & 1;
	}

	bool NiAlphaProperty::GetAlphaTesting() const
	{
		return (alphaFlags >> 9) & 1;
	}

	bool NiAlphaProperty::GetNoSorter() const
	{
		return (alphaFlags >> 13) & 1;
	}

	NiAlphaProperty::AlphaFunction NiAlphaProperty::GetDestBlendMode() const
	{
		return static_cast<AlphaFunction>((alphaFlags >> 5) & 15);
	}

	NiAlphaProperty::AlphaFunction NiAlphaProperty::GetSrcBlendMode() const
	{
		return static_cast<AlphaFunction>((alphaFlags >> 1) & 15);
	}

	NiAlphaProperty::TestFunction NiAlphaProperty::GetAlphaTestMode() const
	{
		return static_cast<TestFunction>((alphaFlags >> 10) & 7);
	}

	void NiAlphaProperty::SetAlphaBlending(bool a_enable)
	{
		if (a_enable) {
			alphaFlags |= 1;
		} else {
			alphaFlags &= ~1;
		}
	}

	void NiAlphaProperty::SetAlphaTesting(bool a_enable)
	{
		if (a_enable) {
			alphaFlags |= 512;
		} else {
			alphaFlags &= ~512;
		}
	}

	void NiAlphaProperty::SetNoSorter(bool a_enable)
	{
		if (a_enable) {
			alphaFlags |= 8192;
		} else {
			alphaFlags &= ~8192;
		}
	}

	void NiAlphaProperty::SetDestBlendMode(AlphaFunction a_mode)
	{
		alphaFlags &= ~480;
		alphaFlags |= 32 * std::to_underlying(a_mode);
	}

	void NiAlphaProperty::SetSrcBlendMode(AlphaFunction a_mode)
	{
		alphaFlags &= ~30;
		alphaFlags |= 2 * std::to_underlying(a_mode);
	}
	void NiAlphaProperty::SetAlphaTestMode(TestFunction a_mode)
	{
		alphaFlags &= ~7168;
		alphaFlags |= 1024 * std::to_underlying(a_mode);
	}
}
