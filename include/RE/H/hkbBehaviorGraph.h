#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefVariant.h"
#include "RE/H/hkbGenerator.h"
#include "RE/H/hkPointerMap.h"

namespace RE
{
	class hkbBehaviorGraphData;
	class hkPseudoRandomGenerator;
	class hkbStateListener;
	class hkbStateMachine;
	class hkbSymbolIdMap;
	class hkbVariableValueSet;

	class hkbBehaviorGraph : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBehaviorGraph;

		enum class VariableMode
		{
			kDiscardWhenActive = 0,
			kMaintainValuesWhenInactive = 1,
		};

		struct StateMachineInfo
		{
			hkbStateMachine*            m_stateMachineTemplate;          // 00
			hkbBehaviorGraph*           m_behaviorTemplate;              // 08
			hkArray<int16_t>*           m_eventlessGlobalTransitions;    // 10
			hkPointerMap<int, int16_t>* m_eventToGlobalTransitionMap;    // 18
			hkArray<int>*               m_childStateMachineInfoIndices;  // 20
			int32_t                     m_parentStateMachineInfoIndex;   // 28
			int32_t                     m_stateIndexInParent;            // 2C
		};
		static_assert(sizeof(StateMachineInfo) == 0x30);

		class GlobalTransitionData : public hkReferencedObject
		{
		public:
			inline static constexpr auto RTTI = RTTI_hkbBehaviorGraph__GlobalTransitionData;

			~GlobalTransitionData() override;  // 00

			hkArray<StateMachineInfo>                m_stateMachineInfos;                             // 10
			hkArray<int>                             m_eventlessGlobalTransitionStateMachineIndices;  // 20
			hkPointerMap<hkbStateMachine*, int>      m_stateMachineTemplateToIndexMap;                // 30
			hkPointerMap<int, hkArray<int>*>         m_eventToStateMachineInfoIndices;                // 40
			hkPointerMap<uint16_t, hkbStateMachine*> m_idToStateMachineTemplateMap;                   // 50
		};
		static_assert(sizeof(GlobalTransitionData) == 0x60);

		~hkbBehaviorGraph() override;  // 00

		// override (hkbGenerator)
		hkClass* GetClassType() const override;																									// 01
		void     CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;								// 02
		void     Activate(const hkbContext& a_context) override;																				// 04
		void     Update(const hkbContext& a_context, float a_timestep) override;																// 05
		void     HandleEvent(const hkbContext& a_context, hkbEvent event) override;																// 06
		void     Deactivate(const hkbContext& a_context) override;																				// 07
		void     GetChildren(stl::enumeration<GetChildrenFlagBits, std::int32_t> flags, ChildrenInfo& childrenInfo) override;					// 09
		hkbNode* CloneNode(hkbBehaviorGraph& rootBehavior) const override;																		// 0C
		bool     IsBehaviorGraph() const override;                                                                                              // 16 - { return 1; }
		void     Generate(const hkbContext& a_context, const hkbGeneratorOutput** activeChildrenOutput, hkbGeneratorOutput& output) override;	// 17
		bool     CanRecycleOutput() override;																									// 18 - { return 1; }
		void     UpdateSync(const hkbContext& a_context) override;																				// 19

		// members
		stl::enumeration<VariableMode, std::uint8_t>			variableMode;                     // 048
		hkArray<uint16_t>										uniqueIDPool;                     // 050
		hkPointerMap<std::uint16_t, hkbStateMachine*>*          idToStateMachineTemplateMap;      // 060
		hkArray<int>											mirroredExternalIDMap;            // 068
		hkPseudoRandomGenerator*								pseudoRandomGenerator;            // 078
		hkRefPtr<hkbGenerator>									rootGenerator;                    // 080
		hkRefPtr<hkbBehaviorGraphData>							data;                             // 088
		hkbGenerator*                                           rootGeneratorClone;               // 090
		hkRefVariant											activeNodes;                      // 098
		hkPointerMap<hkbNode*, int>*							activeNodeTemplateToIndexMap;     // 0A0
		hkRefVariant											activeNodesChildrenIndices;       // 0A8
		hkRefPtr<GlobalTransitionData>                          globalTransitionData;             // 0B0
		hkRefPtr<hkbSymbolIdMap>                                eventIDMap;                       // 0B8
		hkRefPtr<hkbSymbolIdMap>                                attributeIDMap;                   // 0C0
		hkRefPtr<hkbSymbolIdMap>                                variableIDMap;                    // 0C8
		hkRefPtr<hkbSymbolIdMap>                                characterPropertyIDMap;           // 0D0
		hkRefPtr<hkbVariableValueSet>							variableValueSet;                 // 0D8
		hkPointerMap<hkbNode*, hkbNode*>*						nodeTemplateToCloneMap;           // 0E0
		hkPointerMap<hkbNode*, hkbNode*>*						nodeCloneToTemplateMap;           // 0E8
		hkPointerMap<hkbStateListener*, hkbStateListener*>*		stateListenerTemplateToCloneMap;  // 0F0
		hkRefVariant											nodePartitionInfo;                // 0F8
		std::int32_t											numIntermediateOutputs;           // 100
		hkArray<hkRefVariant>									jobs;                             // 108
		hkArray<hkRefVariant>									allPartitionMemory;               // 118
		std::int16_t											numStaticNodes;                   // 128
		std::int16_t											nextUniqueID;                     // 12A
		bool													isActive;                         // 12C
		bool													isLinked;                         // 12D
		bool													updateActiveNodes;                // 12E
		bool													stateOrTransitionChanged;         // 12F
	};
	static_assert(sizeof(hkbBehaviorGraph) == 0x130);
}
