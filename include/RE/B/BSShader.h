#pragma once

#include "RE/B/BSReloadShaderI.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiAccumulator.h"
#include "RE/N/NiBoneMatrixSetterI.h"
#include "RE/N/NiRefObject.h"

#include "REX/W32/D3D11.h"

struct ID3D11Buffer;
struct ID3D11PixelShader;
struct ID3D11VertexShader;

namespace RE
{
	class BSRenderPass;
	class BSShaderMaterial;

	namespace BSGraphics
	{
		enum class ConstantGroupLevel
		{
			PerTechnique,
			PerMaterial,
			PerGeometry,
		};

		class ConstantGroup
		{
		public:
			// members
			REX::W32::ID3D11Buffer* buffer;  // 00
			void*                   data;    // 08
		};
		static_assert(sizeof(ConstantGroup) == 0x10);

		class PixelShader
		{
		public:
			// members
			std::uint32_t                id;                  // 00
			REX::W32::ID3D11PixelShader* shader = nullptr;    // 08
			ConstantGroup                constantBuffers[3];  // 10
			std::array<std::int8_t, 64>  constantTable;       // 58
		};
		static_assert(sizeof(PixelShader) == 0x80);

		class VertexShader
		{
		public:
			// members
			std::uint32_t                 id;                  // 00
			REX::W32::ID3D11VertexShader* shader = nullptr;    // 08
			std::uint32_t                 byteCodeSize;        // 10
			ConstantGroup                 constantBuffers[3];  // 18
			std::uint64_t                 shaderDesc;          // 48
			std::array<std::int8_t, 20>   constantTable;       // 50
			std::uint32_t                 pad64;               // 64
			std::uint8_t                  rawBytecode[0];      // 68
		};
		static_assert(sizeof(VertexShader) == 0x68);
	}

	namespace BSShaderTechniqueIDMap
	{
		template <class T>
		struct HashPolicy
		{
			[[nodiscard]] std::uint32_t operator()(const T a_shader) const noexcept
			{
				assert(a_shader != nullptr);
				return a_shader->id;
			}
		};

		template <class T>
		struct ComparePolicy
		{
			[[nodiscard]] bool operator()(const T a_lhs, const T a_rhs) const noexcept
			{
				assert(a_lhs != nullptr);
				assert(a_rhs != nullptr);
				return a_lhs->id == a_rhs->id;
			}
		};

		template <class T>
		using MapType = BSTSet<T, HashPolicy<T>, ComparePolicy<T>>;
	}

	class BSShader :
		public NiRefObject,          // 00
		public NiBoneMatrixSetterI,  // 10
		public BSReloadShaderI       // 18
	{
	public:
		enum class Type
		{
			None = 0,
			Grass = 1,
			Sky = 2,
			Water = 3,
			BloodSplatter = 4,
			ImageSpace = 5,
			Lighting = 6,
			Effect = 7,
			Utility = 8,
			DistantTree = 9,
			Particle = 10,
			Total,
		};

		inline static constexpr auto RTTI = RTTI_BSShader;
		inline static constexpr auto VTABLE = VTABLE_BSShader;

		~BSShader() override;  // 00

		// add
		virtual bool SetupTechnique(std::uint32_t globalTechnique) = 0;                                          // 02
		virtual void RestoreTechnique(std::uint32_t globalTechnique) = 0;                                        // 03
		virtual void SetupMaterial(const BSShaderMaterial* material);                                            // 04
		virtual void RestoreMaterial(const BSShaderMaterial* material);                                          // 05
		virtual void SetupGeometry(BSRenderPass* pass, RenderFlags flags) = 0;                                   // 06
		virtual void RestoreGeometry(BSRenderPass* pass, RenderFlags flags) = 0;                                 // 07
		virtual void GetTechniqueName(std::uint32_t a_techniqueID, char* a_buffer, std::uint32_t a_bufferSize);  // 08
		virtual void ReloadShaders(bool a_clear);                                                                // 09

		// members
		stl::enumeration<Type, std::int32_t>                       shaderType;     // 20
		BSShaderTechniqueIDMap::MapType<BSGraphics::VertexShader*> vertexShaders;  // 28
		BSShaderTechniqueIDMap::MapType<BSGraphics::PixelShader*>  pixelShaders;   // 58
		const char*                                                fxpFilename;    // 88

	protected:
		bool BeginTechnique(uint32_t vertexDescriptor, uint32_t pixelDescriptor,
			bool skipPixelShader);
		void EndTechnique();

		inline static thread_local uint32_t CurrentTechnique = 0;
	};
	static_assert(sizeof(BSShader) == 0x90);
}
