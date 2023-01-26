#include "RE/N/NiStream.h"

#include "RE/N/NiObject.h"

namespace RE
{
	NiStream* NiStream::ctor()
	{
		using func_t = decltype(&NiStream::ctor);
		REL::Relocation<func_t> func{ RELOCATION_ID(68971, 70324) };
		auto niStream = func(this);
		stl::emplace_vtable<NiStream>(niStream);
		return niStream;
	}

	NiStream* NiStream::Create()
	{
		auto niStream = malloc<NiStream>();
		if (niStream) 
		{
			std::memset(niStream, 0, sizeof(NiStream));
			niStream->ctor();
		}
		return niStream;
	}
}
