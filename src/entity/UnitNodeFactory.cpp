#include "UnitNodeFactory.h"

UnitNodeFactory::UnitNodeFactory()
{

}

QSharedPointer<UnitNode> UnitNodeFactory::makeShare(TypeUnitNode type, QSharedPointer<UnitNode> parent)
{
    QSharedPointer<UnitNode> newUN;
    switch (type) {
    case TypeUnitNode::SYSTEM    : {newUN = QSharedPointer<UnitNode_SYSTEM>   ::create(parent); break;}//(new UnitNode_SYSTEM(parent)); break;}
    case TypeUnitNode::GROUP     : {newUN = QSharedPointer<UnitNode_GROUP>    ::create(parent); break;}//(new UnitNode_GROUP(parent)); break;}
    case TypeUnitNode::KL        : {newUN = QSharedPointer<UnitNode_KL>       ::create(parent); break;}//(new UnitNode_KL(parent)); break;}
    case TypeUnitNode::SD_BL_IP  : {newUN = QSharedPointer<UnitNode_SD_BL_IP> ::create(parent); break;}//(new UnitNode_SD_BL_IP(parent)); break;}
    case TypeUnitNode::IU_BL_IP  : {newUN = QSharedPointer<UnitNode_IU_BL_IP> ::create(parent); break;}//(new UnitNode_IU_BL_IP(parent)); break;}
    case TypeUnitNode::TG        : {newUN = QSharedPointer<UnitNode_TG>       ::create(parent); break;}//(new UnitNode_TG(parent)); break;}
    case TypeUnitNode::TG_Base   : {newUN = QSharedPointer<UnitNode_TG>       ::create(parent); break;}//(new UnitNode_TG(parent)); break;}
    case TypeUnitNode::RLM_KRL   : {newUN = QSharedPointer<UnitNode_RLM_KRL>  ::create(parent); break;}//(new UnitNode_RLM_KRL(parent)); break;}
    case TypeUnitNode::RLM_C     : {newUN = QSharedPointer<UnitNode_RLM_C>    ::create(parent); break;}//(new UnitNode_RLM_C(parent)); break;}
    case TypeUnitNode::BOD_T4K_M : {newUN = QSharedPointer<UnitNode_BOD_T4K_M>::create(parent); break;}//(new UnitNode_BOD_T4K_M(parent)); break;}
    case TypeUnitNode::Y4_T4K_M  : {newUN = QSharedPointer<UnitNode_Y4_T4K_M> ::create(parent); break;}//(new UnitNode_Y4_T4K_M(parent)); break;}
    case TypeUnitNode::DD_T4K_M  : {newUN = QSharedPointer<UnitNode_DD_T4K_M> ::create(parent); break;}//(new UnitNode_DD_T4K_M(parent)); break;}
    case TypeUnitNode::BOD_SOTA  : {newUN = QSharedPointer<UnitNode_BOD_SOTA> ::create(parent); break;}//(new UnitNode_BOD_SOTA(parent)); break;}
    case TypeUnitNode::Y4_SOTA   : {newUN = QSharedPointer<UnitNode_Y4_SOTA>  ::create(parent); break;}//(new UnitNode_Y4_SOTA(parent)); break;}
    case TypeUnitNode::DD_SOTA   : {newUN = QSharedPointer<UnitNode_DD_SOTA>  ::create(parent); break;}//(new UnitNode_DD_SOTA(parent)); break;}
    case TypeUnitNode::BL_IP     : {newUN = QSharedPointer<UnitNode_BL_IP>    ::create(parent); break;}//(new UnitNode_BL_IP(parent)); break;}
    default                      : {newUN = QSharedPointer<UnitNode>          ::create(parent); break;}//(new UnitNode(parent)); break;}
    }
    if(!newUN.isNull())
        newUN->setType(type);
    return newUN;
}

QSharedPointer<UnitNode> UnitNodeFactory::makeShare(const UnitNode & parent)
{
    QSharedPointer<UnitNode> newUN;
    switch (parent.getType()) {
    case TypeUnitNode::SYSTEM    : {newUN = QSharedPointer<UnitNode_SYSTEM>   ::create(parent); break;}//(new UnitNode_SYSTEM(parent)); break;}
    case TypeUnitNode::GROUP     : {newUN = QSharedPointer<UnitNode_GROUP>    ::create(parent); break;}//(new UnitNode_GROUP(parent)); break;}
    case TypeUnitNode::KL        : {newUN = QSharedPointer<UnitNode_KL>       ::create(parent); break;}//(new UnitNode_KL(parent)); break;}
    case TypeUnitNode::SD_BL_IP  : {newUN = QSharedPointer<UnitNode_SD_BL_IP> ::create(parent); break;}//(new UnitNode_SD_BL_IP(parent)); break;}
    case TypeUnitNode::IU_BL_IP  : {newUN = QSharedPointer<UnitNode_IU_BL_IP> ::create(parent); break;}//(new UnitNode_IU_BL_IP(parent)); break;}
    case TypeUnitNode::TG        : {newUN = QSharedPointer<UnitNode_TG>       ::create(parent); break;}//(new UnitNode_TG(parent)); break;}
    case TypeUnitNode::TG_Base   : {newUN = QSharedPointer<UnitNode_TG>       ::create(parent); break;}//(new UnitNode_TG(parent)); break;}
    case TypeUnitNode::RLM_KRL   : {newUN = QSharedPointer<UnitNode_RLM_KRL>  ::create(parent); break;}//(new UnitNode_RLM_KRL(parent)); break;}
    case TypeUnitNode::RLM_C     : {newUN = QSharedPointer<UnitNode_RLM_C>    ::create(parent); break;}//(new UnitNode_RLM_C(parent)); break;}
    case TypeUnitNode::BOD_T4K_M : {newUN = QSharedPointer<UnitNode_BOD_T4K_M>::create(parent); break;}//(new UnitNode_BOD_T4K_M(parent)); break;}
    case TypeUnitNode::Y4_T4K_M  : {newUN = QSharedPointer<UnitNode_Y4_T4K_M> ::create(parent); break;}//(new UnitNode_Y4_T4K_M(parent)); break;}
    case TypeUnitNode::DD_T4K_M  : {newUN = QSharedPointer<UnitNode_DD_T4K_M> ::create(parent); break;}//(new UnitNode_DD_T4K_M(parent)); break;}
    case TypeUnitNode::BOD_SOTA  : {newUN = QSharedPointer<UnitNode_BOD_SOTA> ::create(parent); break;}//(new UnitNode_BOD_SOTA(parent)); break;}
    case TypeUnitNode::Y4_SOTA   : {newUN = QSharedPointer<UnitNode_Y4_SOTA>  ::create(parent); break;}//(new UnitNode_Y4_SOTA(parent)); break;}
    case TypeUnitNode::DD_SOTA   : {newUN = QSharedPointer<UnitNode_DD_SOTA>  ::create(parent); break;}//(new UnitNode_DD_SOTA(parent)); break;}
    case TypeUnitNode::BL_IP     : {newUN = QSharedPointer<UnitNode_BL_IP>    ::create(parent); break;}//(new UnitNode_BL_IP(parent)); break;}
    default                      : {newUN = QSharedPointer<UnitNode>          ::create(parent); break;}//(new UnitNode(parent)); break;}
    }
    if(!newUN.isNull())
        newUN->setType(parent.getType());
    return newUN;
}
