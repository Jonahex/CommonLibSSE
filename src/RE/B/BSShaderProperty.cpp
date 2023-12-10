#include "RE/B/BSShaderProperty.h"

#include "RE/B/BSRenderPass.h"
#include "RE/B/BSUtilityShader.h"

namespace RE
{
	void BSShaderProperty::RenderPassArray::Clear()
	{
		while (head != nullptr)
		{
			BSRenderPass* next = head->next;
			head->Clear();
			head = next;
		}
		head = nullptr;
	}

	void BSShaderProperty::RenderPassArray::ClearAfter(BSRenderPass* pass)
	{
		if (pass == nullptr)
		{
			Clear();
			return;
		}

		BSRenderPass* current = pass->next;
		pass->next = nullptr;
		while (current != nullptr)
		{
			BSRenderPass* next = current->next;
			current->Clear();
			current = next;
		}
	}

	BSRenderPass* BSShaderProperty::RenderPassArray::EmplacePass(BSShader* shader, BSShaderProperty* property, BSGeometry* geometry,
		uint32_t technique, uint8_t numLights, BSLight* light0, BSLight* light1,
		BSLight* light2, BSLight* light3)
	{
		BSLight* lights[4];
		lights[0] = light0;
		lights[1] = light1;
		lights[2] = light2;
		lights[3] = light3;
		auto* newPass = BSRenderPass::Make(shader, property, geometry, technique, numLights, lights);
		if (head != nullptr) 
		{
			BSRenderPass* lastPass = head;
			while (lastPass->next != nullptr)
			{
				lastPass = lastPass->next;
			}
			lastPass->next = newPass;
		} 
		else 
		{
			head = newPass;
		}
		return newPass;
	}

	BSRenderPass* BSShaderProperty::RenderPassArray::SetPass(BSRenderPass* pass, BSShader* shader, BSShaderProperty* property, BSGeometry* geometry,
		uint32_t technique)
	{
		if (pass == nullptr)
		{
			return EmplacePass(shader, property, geometry, technique);
		}
		pass->shader = shader;
		pass->shaderProperty = property;
		pass->passEnum = technique;
		pass->accumulationHint = BSRenderPass::AccumulationHint::Unk0;
		pass->LODMode.index = 3;
		pass->LODMode.singleLevel = false;

		return pass;
	}

	BSRenderPass* BSShaderProperty::RenderPassArray::MoveHead(RenderPassArray& that)
	{
		auto oldHead = head;
		head = head->next;
		oldHead->next = that.head;
		that.head = oldHead;
		return oldHead;
	}

	void BSShaderProperty::SetEffectShaderData(const BSTSmartPointer<BSEffectShaderData>& a_data)
	{
		lastRenderPassState = std::numeric_limits<std::int32_t>::max();
		effectData = a_data;
	}

	void BSShaderProperty::SetMaterial(BSShaderMaterial* a_material, bool a_unk1)
	{
		using func_t = decltype(&BSShaderProperty::SetMaterial);
		REL::Relocation<func_t> func{ RELOCATION_ID(98897, 105544) };
		return func(this, a_material, a_unk1);
	}

	void BSShaderProperty::SetFlags(EShaderPropertyFlag8 a_flag, bool a_set)
	{
		using func_t = decltype(&BSShaderProperty::SetFlags);
		REL::Relocation<func_t> func{ RELOCATION_ID(98893, 105540) };
		return func(this, a_flag, a_set);
	}

	BSShaderProperty::RenderPassArray* BSShaderProperty::GetDebugRenderPasses(BSGeometry* geometry)
	{
		const uint32_t utilityTechnique = DetermineUtilityShaderDecl();
		if (utilityTechnique != 0) 
		{
			debugRenderPassList.EmplacePass(BSUtilityShader::GetSingleton(), this, geometry, 
				static_cast<uint32_t>(ShaderTechnique::UtilityGeneralStart) + 
				(utilityTechnique | static_cast<uint32_t>(RE::BSUtilityShader::Flags::DebugColor)));
		}
		return &debugRenderPassList;
	}

	void BSShaderProperty::SetAlpha(float newAlpha)
	{
		if (IsTranslucent() != newAlpha < 1.f)
		{
			lastRenderPassState = std::numeric_limits<std::int32_t>::max();
		}
		alpha = newAlpha;
	}

	bool BSShaderProperty::IsTranslucent() const
	{
		return alpha < 1.f;
	}

	bool BSShaderProperty::CanBeAffectedByLight(BSLight* light) const
	{
		using enum EShaderPropertyFlag;

		if (!light->affectLand && flags.any(kMultiTextureLandscape, kNoLODLandBlend))
		{
			return false;
		}
		return true;
	}
}
