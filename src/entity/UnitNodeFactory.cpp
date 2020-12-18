#include "UnitNodeFactory.h"

UnitNodeFactory::UnitNodeFactory()
{

}

UnitNode *UnitNodeFactory::make(TypeUnitNode type, UnitNode * parent)
{
    UnitNode * newUN = nullptr;
    switch (type) {
    case TypeUnitNode::SYSTEM : {newUN = new UnitNode_SYSTEM(parent); break;}
    case TypeUnitNode::GROUP : {newUN = new UnitNode_GROUP(parent); break;}
    case TypeUnitNode::KL : {newUN = new UnitNode_KL(parent); break;}
    case TypeUnitNode::SD_BL_IP : {newUN = new UnitNode_SD_BL_IP(parent); break;}
    case TypeUnitNode::IU_BL_IP : {newUN = new UnitNode_IU_BL_IP(parent); break;}
    case TypeUnitNode::TG : {newUN = new UnitNode_TG(parent); break;}
    case TypeUnitNode::RLM_KRL : {newUN = new UnitNode_RLM_KRL(parent); break;}
    case TypeUnitNode::RLM_C : {newUN = new UnitNode_RLM_C(parent); break;}
    case TypeUnitNode::BOD_T4K_M : {newUN = new UnitNode_BOD_T4K_M(parent); break;}
    case TypeUnitNode::Y4_T4K_M : {newUN = new UnitNode_Y4_T4K_M(parent); break;}
    case TypeUnitNode::DD_T4K_M : {newUN = new UnitNode_DD_T4K_M(parent); break;}
    case TypeUnitNode::BOD_SOTA : {newUN = new UnitNode_BOD_SOTA(parent); break;}
    case TypeUnitNode::Y4_SOTA : {newUN = new UnitNode_Y4_SOTA(parent); break;}
    case TypeUnitNode::DD_SOTA : {newUN = new UnitNode_DD_SOTA(parent); break;}
    case TypeUnitNode::BL_IP : {newUN = new UnitNode_BL_IP(parent); break;}
    default: {newUN = new UnitNode(parent); break;}
    }
    if(nullptr != newUN)
        newUN->setType(type);
    return newUN;
}

UnitNode *UnitNodeFactory::make(const UnitNode & parent)
{
    UnitNode * newUN = nullptr;
    switch (parent.getType()) {
    case TypeUnitNode::SYSTEM : {newUN = new UnitNode_SYSTEM(parent); break;}
    case TypeUnitNode::GROUP : {newUN = new UnitNode_GROUP(parent); break;}
    case TypeUnitNode::KL : {newUN = new UnitNode_KL(parent); break;}
    case TypeUnitNode::SD_BL_IP : {newUN = new UnitNode_SD_BL_IP(parent); break;}
    case TypeUnitNode::IU_BL_IP : {newUN = new UnitNode_IU_BL_IP(parent); break;}
    case TypeUnitNode::TG : {newUN = new UnitNode_TG(parent); break;}
    case TypeUnitNode::RLM_KRL : {newUN = new UnitNode_RLM_KRL(parent); break;}
    case TypeUnitNode::RLM_C : {newUN = new UnitNode_RLM_C(parent); break;}
    case TypeUnitNode::BOD_T4K_M : {newUN = new UnitNode_BOD_T4K_M(parent); break;}
    case TypeUnitNode::Y4_T4K_M : {newUN = new UnitNode_Y4_T4K_M(parent); break;}
    case TypeUnitNode::DD_T4K_M : {newUN = new UnitNode_DD_T4K_M(parent); break;}
    case TypeUnitNode::BOD_SOTA : {newUN = new UnitNode_BOD_SOTA(parent); break;}
    case TypeUnitNode::Y4_SOTA : {newUN = new UnitNode_Y4_SOTA(parent); break;}
    case TypeUnitNode::DD_SOTA : {newUN = new UnitNode_DD_SOTA(parent); break;}
    case TypeUnitNode::BL_IP : {newUN = new UnitNode_BL_IP(parent); break;}
    default: {newUN = new UnitNode(parent); break;}
    }
    return newUN;
}
