#include "RE/T/TESWaterForm.h"

#include "RE/Offsets.h"

namespace RE
{
    void TESWaterForm::FillMaterial(BSWaterShaderMaterial& material) const
	{
		using func_t = decltype(&TESWaterForm::FillMaterial);
        const REL::Relocation<func_t> func{ Offset::TESWaterForm::FillMaterial };
		func(this, material);
    }
}
