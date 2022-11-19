#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESTexture : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESTexture;

		// override (BaseFormComponent)
		~TESTexture() override = default;											// 00

		void InitializeDataComponent() override										// 01
		{
			textureName = {};
		}
		void ClearDataComponent() override											// 02
		{}
		void CopyComponent(BaseFormComponent* a_rhs) override						// 03
		{
			if (auto other = dynamic_cast<TESTexture*>(a_rhs)) 
			{
				textureName = other->textureName;
			}
		}

		// add
		virtual std::uint32_t GetMaxAllowedSize()									// 04
		{
			return 0;
		}
		virtual const char* GetAsNormalFile(BSString& a_out) const					// 05
		{
			if (!textureName.empty())
			{
				const std::string_view originalName(textureName.c_str());
				const auto dotPosition = originalName.find_last_of('.');
				if (dotPosition != std::string_view::npos) 
				{
					const std::string_view textureNameWithoutExtension = originalName.substr(0, dotPosition);
					a_out = std::format("{}_n.dds", textureNameWithoutExtension);
					if (!a_out.empty())
					{
						return a_out.c_str();
					}
				}
			}
			return nullptr;
		}
		[[nodiscard]] virtual const char* GetDefaultPath() const					// 06
		{
			return "Textures\\";
		}

		// members
		BSFixedString textureName;  // 08 - ICON
	};
	static_assert(sizeof(TESTexture) == 0x10);
}
