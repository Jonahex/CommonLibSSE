#include "RE/B/BSShader.h"

namespace RE
{
	bool BSShader::BeginTechnique(uint32_t vertexDescriptor, uint32_t pixelDescriptor,
		bool skipPixelShader)
	{
		using func_t = decltype(&BSShader::BeginTechnique);
		REL::Relocation<func_t> func{ RELOCATION_ID(101341, 108328) };
		return func(this, vertexDescriptor, pixelDescriptor, skipPixelShader);
	}

	void BSShader::EndTechnique()
	{

	}
}
